Drone::Drone(float mass, std::vector<float> x_initial, std::vector<float> v_initial)
{
    this->mass = mass;
    this->x.push_back(x_initial);
    this->v.push_back(v_initial);
    this->resetRequiredForce();
    this->resetProximityCount();
}

Drone::~Drone()
{
}

void Drone::applyForce(std::vector<float> force, float dt)
{
    std::vector<float> temp_a(2), temp_v(2), temp_x(2);
    for (int k = 0; k < 2; k++)
    {
        temp_a[k] = force[k] / this->mass;
        temp_v[k] = this->v.back()[k] + temp_a[k] * dt;
        temp_x[k] = this->x.back()[k] + this->v.back()[k] * dt;
    }
    this->v.push_back(temp_v);
    this->x.push_back(temp_x);
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
    /**
    if (this->isChanged)
    {
        for (auto it = this->_observers.begin(); it != this->_observers.end(); ++it)
        {
            (*it)->update();
        }
        this->isChanged = false;
    }
    **/
    _observer->update(reqForce);
}

void Drone::setChanged()
{
    this->isChanged = true;
}

void Drone::update(std::vector<float> reqForce)
{
    for (int k = 0; k < 2; k++)
    {
        this->requiredForce[k] = reqForce[k];
    }
    this->proximityCount++;
}

void Drone::checkProximity()
{
    for (_Observer *obs : this->_observers)
    {
        Drone *drn = (Drone *)obs;
        std::vector<float> reqForce(2);
        std::vector<float> r = this->getR(drn);
        float dist = this->getDistance(r);
        if (dist < this->proximityCaution)
        {
            for (int k = 0; k < 2; k++)
            {
                reqForce[k] = r[k] * dist * this->forceCoeff;
            }
            this->notify(drn, reqForce);
        }
        else
        {
            this->notify(drn,{0.0, 0.0});
        }
    }
}



std::vector<float> Drone::getX()
{
    return this->x.back();
}

std::vector<float> Drone::getV()
{
    return this->v.back();
}

std::vector<std::vector<float>> Drone::getXHistory()
{
    return this->x;
}

std::vector<std::vector<float>> Drone::getVHistory()
{
    return this->v;
}
std::vector<float> Drone::getR(Drone *drn)
{
    std::vector<float> r(2);
    for (int k = 0; k < 2; k++)
    {
        r[k] = drn->getX()[k] - this->getX()[k];
    }
    return r;
}

float Drone::getDistance(std::vector<float> r)
{
    float dist = 0.0;
    for (int k = 0; k < 2; k++)
    {
        dist += pow(r[k], 2);
    }
    return dist;
}

std::vector<float> Drone::getRequiredForce()
{
    return this->requiredForce;
}

void Drone::increaseProximityCount()
{
    this->proximityCount++;
}

void Drone::addRequiredForce(std::vector<float> reqForce)
{
    for (int k = 0; k < 2; k++)
    {
        this->requiredForce[k] += reqForce[k];
    }
}

void Drone::resetProximityCount()
{
    this->proximityCount = 0;
}

void Drone::resetRequiredForce()
{
    this->requiredForce = {0.0, 0.0};
}