Drone::Drone(float mass, std::vector<float> x_initial, std::vector<float> v_initial)
{
    this->mass = mass;
    this->x.push_back(x_initial);
    this->v.push_back(v_initial);
    this->SetProximityCount(1);
    this->SetProximityForce({0.0, 0.0});
    this->SetMass(1.0);
    this->SetProximityCautionDistance(3);
    this->SetProximityCoeff(0.001);
    this->SetTargetCoeff(0.001);
    this->SetC_D(10.0);
    this->SetRho(1.225);
    this->SetS(0.5);
    this->SetGoToLocation({1.0, 1.0});
}

Drone::~Drone()
{
}

void Drone::propagate(float dt)
{
    float temp_a;
    std::vector<float> temp_v(2, 0.0), temp_x(2, 0.0);

    std::vector<float> dragForce = this->calculateDrag();
    std::vector<float> targetForce = {0,0};// this->calculateTargetForce();
    std::vector<float> proximityForce = this->calculateProximityForce();

    for (int k = 0; k < 2; k++)
    {
        temp_a = ((proximityForce[k] / this->getProximityCount()) - dragForce[k] + targetForce[k]) / this->GetMass();
        temp_v[k] = this->getVFinal()[k] + temp_a * dt;
        temp_x[k] = this->getXFinal()[k] + this->getVFinal()[k] * dt;
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
    std::vector<float> dragForce(2);
    std::vector<float> v = this->getVFinal();
    float vMag = pow(v[0], 2) + pow(v[1], 2);
    float dragForceMag = pow(vMag, 2) * 0.5 * this->rho * this->S * this->C_D;
    for (int k = 0; k < 2; k++)
    {
        if (vMag != 0.0)
        {
            v[k] /= vMag;
        }
        

        dragForce[k] = dragForceMag * v[k];
    }
    return dragForce;
}

std::vector<float> Drone::calculateTargetForce()
{
    std::vector<float> targetForce(2), rTarget(2);
    for (int k = 0; k < 2; k++)
    {
        rTarget[k] = this->GetGoToLocation()[k] - this->getXFinal()[k];
        targetForce[k] = rTarget[k] * this->GetTargetCoeff();
    }

    

    return targetForce;
}

std::vector<float> Drone::calculateProximityForce()
{
    return this->getProximityForce();
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
        SetForce[k] = this->getProximityForce()[k] + reqForce[k];
    }
    this->SetProximityForce(SetForce);

    this->SetProximityCount(this->getProximityCount() + 1);
}

std::vector<float> Drone::getXFinal()
{
    return this->x.back();
}

std::vector<float> Drone::getVFinal()
{
    return this->v.back();
}

std::vector<std::vector<float>> Drone::getX()
{
    return this->x;
}

std::vector<std::vector<float>> Drone::getV()
{
    return this->v;
}

int Drone::getProximityCount()
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

std::vector<float> Drone::getProximityForce()
{
    return this->proximityForce;
}

std::vector<float> Drone::calculateRVector(Drone *drn)
{
    std::vector<float> r(2);
    for (int k = 0; k < 2; k++)
    {
        r[k] = drn->getXFinal()[k] - this->getXFinal()[k];
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

float Drone::GetTargetCoeff()
{
    return this->targetCoeff;
}

void Drone::SetTargetCoeff(float targetCoeff)
{
    this->targetCoeff = targetCoeff;
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

std::vector<float> Drone::GetGoToLocation()
{
    return this->goToLocation;
}

void Drone::SetGoToLocation(std::vector<float> goToLocation)
{
    this->goToLocation = goToLocation;
}

std::vector<_Observer *> Drone::get_Observers()
{
    return this->_observers;
}

void Drone::Set_Observers(std::vector<_Observer *> _observers)
{
    this->_observers = _observers;
}