Drone::Drone(float mass, std::vector<float> x_initial, std::vector<float> v_initial)
{
    this->mass = mass;
    this->x.push_back(x_initial);
    this->v.push_back(v_initial);
    this->SetProximityCount(1);
    this->SetProximityForce({0.0, 0.0});
    this->SetExternalForce({0.0, 0.0});
    this->SetMass(0.5);
    this->SetProximityCautionDistance(3);
    this->SetProximityCoeff(0.001);
    this->SetTargetSpringCoeff(0.001);
    this->SetTargetDampingCoeff(10.0);
    this->SetC_D(0.5);
    this->SetRho(1.225);
    this->SetS(0.5);
    this->SetTarget({0.0, 10.0});
    this->SetAerodynamicsEffectMode(true);
    this->SetProximityCautionMode(false);
    this->SetTargetChaseMode(true);
    this->SetExternalForceMode(true);
}

Drone::~Drone()
{
}

void Drone::propagate(float dt)
{
    float temp_a;
    std::vector<float> temp_v(2, 0.0), temp_x(2, 0.0), dragForce(2, 0.0), targetForce(2, 0.0), _proximityForce(2, 0.0), _externalForce(2, 0.0);

    if (this->GetAerodynamicsEffectMode())
        dragForce = this->calculateDrag();
    if (this->GetTargetChaseMode())
        targetForce = this->calculateTargetForce();
    if (this->GetProximityCautionMode())
        _proximityForce = this->calculateProximityForce();
    if (this->GetExternalForceMode())
        _externalForce = this->calculateExternalForce();

    //std::cout << "Drag Force = [" << dragForce[0] << " " << dragForce[1] << "]" << std::endl;
    //std::cout << "Target Force = [" << targetForce[0] << " " << targetForce[1] << "]" << std::endl;
    //std::cout << "Proximity Force = [" << _proximityForce[0] << " " << _proximityForce[1] << "]" << std::endl;
    //std::cout << "External Force = [" << _externalForce[0] << " " << _externalForce[1] << "]" << std::endl;

    for (int k = 0; k < 2; k++)
    {
        temp_a = ((_proximityForce[k] / this->GetProximityCount()) + dragForce[k] + targetForce[k] + _externalForce[k]) / this->GetMass();
        temp_v[k] = this->GetVFinal()[k] + temp_a * dt;
        temp_x[k] = this->GetXFinal()[k] + this->GetVFinal()[k] * dt;
    }
    this->v.push_back(temp_v);
    this->x.push_back(temp_x);
}

void Drone::checkProximity()
{
    for (_Observer *obs : this->_observers)
    {
        Drone *drn = (Drone *)obs;
        std::vector<float> reqForce(2);
        std::vector<float> r = this->calculateRVector(drn);
        float dist = this->calculateDistanceFromRVector(r);
        if (dist < this->GetProximityCautionDistance())
        {
            for (int k = 0; k < 2; k++)
            {
                reqForce[k] = r[k] * this->proximityCoeff * dist;
            }
            this->notify(drn, reqForce);
        }
        else
        {
            this->notify(drn, {0.0, 0.0});
        }
    }
}

std::vector<float> Drone::calculateDrag()
{
    std::vector<float> dragForce(2, 0.0);
    std::vector<float> v = this->GetVFinal();
    float vMag = sqrt(pow(v[0], 2) + pow(v[1], 2));
    float dragForceMag = pow(vMag, 2) * 0.5 * this->rho * this->S * this->C_D;
    if (vMag != 0.0)
    {
        for (int k = 0; k < 2; k++)
        {
            v[k] /= vMag;
            dragForce[k] = -dragForceMag * v[k];
        }
    }
    else
    {
        dragForce = {0.0, 0.0};
    }
    return Drone::saturate(dragForce, INFINITY);
}

std::vector<float> Drone::calculateTargetForce()
{

    std::vector<float> targetForce(2), rTarget(2);
    std::vector<float> v = this->GetVFinal();
    float vMag = 0;
    float rTargetMag = 0;

    for (int k = 0; k < 2; k++)
    {   
        rTarget[k] = this->GetTarget()[k] - this->GetXFinal()[k];
        rTargetMag += pow(rTarget[k],2);
        vMag += pow(v[k], 2);
    }
    vMag = sqrt(vMag);
    rTargetMag = sqrt(rTargetMag);

    for (int k = 0; k < 2; k++)
    {
        rTarget[k] /= rTargetMag;
        targetForce[k] = (rTargetMag * this->GetTargetSpringCoeff() + vMag * this->GetTargetDampingCoeff()) * rTarget[k];
    }

    return Drone::saturate(targetForce, INFINITY);
}

std::vector<float> Drone::calculateProximityForce()
{
    return Drone::saturate(this->GetProximityForce(), INFINITY);
}

std::vector<float> Drone::calculateExternalForce()
{
    return this->GetExternalForce();
}

std::vector<float> Drone::saturate(std::vector<float> vec, float saturationVal)
{
    int size = vec.size();
    for (int k = 0; k < size; k++)
    {
        if (vec[k] > saturationVal)
        {
            vec[k] = saturationVal;
        }
        else if (vec[k] < -saturationVal)
        {
            vec[k] = -saturationVal;
        }
    }
    return vec;
}

void Drone::addObserver(_Observer *_observer)
{
    this->_observers.push_back(_observer);
}

void Drone::removeObserver(_Observer *_observer)
{
    std::vector<_Observer *>::iterator it = std::find(this->_observers.begin(), this->_observers.end(), _observer);
    if (it != this->_observers.end())
    {
        this->_observers.erase(it);
    }
}

void Drone::notify(_Observer *_observer, std::vector<float> reqForce)
{
    _observer->update(reqForce);
}

void Drone::update(std::vector<float> reqForce)
{
    std::vector<float> SetForce(2);
    for (int k = 0; k < 2; k++)
    {
        SetForce[k] = this->GetProximityForce()[k] + reqForce[k];
    }
    this->SetProximityForce(SetForce);

    this->SetProximityCount(this->GetProximityCount() + 1);
}

std::vector<float> Drone::GetXFinal()
{
    return this->x.back();
}

std::vector<float> Drone::GetVFinal()
{
    return this->v.back();
}

std::vector<std::vector<float>> Drone::GetX()
{
    return this->x;
}

std::vector<std::vector<float>> Drone::GetV()
{
    return this->v;
}

int Drone::GetProximityCount()
{
    return this->proximityCount;
}

void Drone::SetProximityCount(int count)
{
    this->proximityCount = count;
}

void Drone::SetProximityForce(std::vector<float> force)
{
    this->proximityForce = force;
}

std::vector<float> Drone::GetProximityForce()
{
    return this->proximityForce;
}

std::vector<float> Drone::calculateRVector(Drone *drn)
{
    std::vector<float> r(2);
    for (int k = 0; k < 2; k++)
    {
        r[k] = drn->GetXFinal()[k] - this->GetXFinal()[k];
    }
    return r;
}

float Drone::calculateDistanceFromRVector(std::vector<float> r)
{
    float dist = 0.0;
    for (int k = 0; k < 2; k++)
    {
        dist += pow(r[k], 2);
    }
    dist = sqrt(dist);
    return dist;
}

float Drone::GetMass()
{
    return this->mass;
}

void Drone::SetMass(float mass)
{
    this->mass = mass;
}

float Drone::GetProximityCautionDistance()
{
    return this->proximityCautionDistance;
}

void Drone::SetProximityCautionDistance(float proximityCautionDistance)
{
    this->proximityCautionDistance = proximityCautionDistance;
}

float Drone::GetProximityCoeff()
{
    return this->proximityCoeff;
}

void Drone::SetProximityCoeff(float proximityCoeff)
{
    this->proximityCoeff = proximityCoeff;
}

float Drone::GetTargetSpringCoeff()
{
    return this->targetSpringCoeff;
}

void Drone::SetTargetSpringCoeff(float targetSpringCoeff)
{
    this->targetSpringCoeff = targetSpringCoeff;
}

float Drone::GetTargetDampingCoeff()
{
    return this->targetDampingCoeff;
}

void Drone::SetTargetDampingCoeff(float targetDapingCoeff)
{
    this->targetDampingCoeff = targetDampingCoeff;
}

float Drone::GetC_D()
{
    return this->C_D;
}

void Drone::SetC_D(float C_D)
{
    this->C_D = C_D;
}

float Drone::GetRho()
{
    return this->rho;
}

void Drone::SetRho(float rho)
{
    this->rho = rho;
}

float Drone::GetS()
{
    return this->S;
}

void Drone::SetS(float S)
{
    this->S = S;
}

std::vector<float> Drone::GetTarget()
{
    return this->target;
}

void Drone::SetTarget(std::vector<float> target)
{
    this->target = target;
}

std::vector<_Observer *> Drone::Get_Observers()
{
    return this->_observers;
}

void Drone::Set_Observers(std::vector<_Observer *> _observers)
{
    this->_observers = _observers;
}

void Drone::SetTargetChaseMode(bool targetChaseMode)
{
    this->targetChaseMode = targetChaseMode;
}

void Drone::SetProximityCautionMode(bool proximityCautionMode)
{
    this->proximityCautionMode = proximityCautionMode;
}

void Drone::SetAerodynamicsEffectMode(bool aerodynamicEffectMode)
{
    this->aerodynamicEffectMode = aerodynamicEffectMode;
}

void Drone::SetExternalForceMode(bool externalForceMode)
{
    this->externalForceMode = externalForceMode;
}

bool Drone::GetTargetChaseMode()
{
    return this->targetChaseMode;
}

bool Drone::GetProximityCautionMode()
{
    return this->proximityCautionMode;
}

bool Drone::GetAerodynamicsEffectMode()
{
    return this->aerodynamicEffectMode;
}

bool Drone::GetExternalForceMode()
{
    return this->externalForceMode;
}

void Drone::SetExternalForce(std::vector<float> externalForce)
{
    this->externalForce = externalForce;
}

std::vector<float> Drone::GetExternalForce()
{
    return this->externalForce;
}