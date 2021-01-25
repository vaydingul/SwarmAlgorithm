

Drone::Drone(std::vector<float> x_initial, std::vector<float> v_initial)
{
    this->x.push_back(x_initial);
    this->v.push_back(v_initial);
    this->SetProximityCount(1);
    this->SetMass(0.5);
    this->SetProximityCautionDistance(1.0);
    this->SetProximityCoeff(0.01);
    this->SetTargetSpringCoeff(0.0001);
    this->SetTargetDampingCoeff(0.0001);
    this->SetC_D(0.5);
    this->SetRho(1.225);
    this->SetS(0.5);
    this->SetTarget({20.0, 20.0});

    this->add_ForceModel(new TargetChaseModel(this, true));
    this->add_ForceModel(new DragModel(this, true));
    this->add_ForceModel(new ExternalForceModel(this, true));
    this->add_ForceModel(new ProximityCautionModel(this, true));
}

Drone::~Drone()
{
}

void Drone::propagate(float dt)
{
    float temp_a;
    std::vector<float> temp_v(2, 0.0), temp_x(2, 0.0), force(2, 0.0);

    for (_ForceModel *_forceModel : this->Get_ForceModels())
    {
        if (_forceModel->GetIsActive())
        {
            for (int i = 0; i < 2; i++)
            {
                force[i] += _forceModel->GetForce()[i];
            }
        }
    }

    for (int k = 0; k < 2; k++)
    {
        temp_a = force[k] / this->GetMass();
        temp_v[k] = this->GetVFinal()[k] + temp_a * dt;
        temp_x[k] = this->GetXFinal()[k] + this->GetVFinal()[k] * dt;
    }
    this->v.push_back(temp_v);
    this->x.push_back(temp_x);
}

void Drone::calculateForceModels()
{
    for(_ForceModel *_forcemodel : this->Get_ForceModels())
    {
        _forcemodel->calculate();
    }
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
    //_observer->update(reqForce);
}

void Drone::update()
{
    /**
    std::vector<float> SetForce(2);
    for (int k = 0; k < 2; k++)
    {
        SetForce[k] = this->GetProximityForce()[k] + reqForce[k];
    }
    this->SetProximityForce(SetForce);

    this->SetProximityCount(this->GetProximityCount() + 1);
    **/
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

void Drone::SetTargetDampingCoeff(float targetDampingCoeff)
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

std::vector<_ForceModel *> Drone::Get_ForceModels()
{
    return this->_ForceModels;
}
void Drone::Set_ForceModels(std::vector<_ForceModel *> _ForceModels)
{
    this->_ForceModels = _ForceModels;
}

void Drone::add_ForceModel(_ForceModel *_ForceModel)
{
    this->_ForceModels.push_back(_ForceModel);
}