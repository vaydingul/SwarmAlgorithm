Drone::Drone(float mass, std::vector<float> x_initial, std::vector<float> v_initial)
{
    this->mass = mass;
    this->x.push_back(x_initial);
    this->v.push_back(v_initial);
    this->goToLocation = {20.0, 20.0};
    this->resetRequiredForce(); // It allocates the sufficient memory for required force
    this->resetProximityCount();
}

Drone::~Drone()
{
}

void Drone::propagate(float dt)
{
    std::vector<float> temp_a(2), temp_v(2), temp_x(2);

    
    std::vector<float> dragForce = this->calculateDrag();
    std::vector<float> targetForce = this->calculateTargetForce();
    std::vector<float> proximityForce = this->getRequiredForce();

    for (int k = 0; k < 2; k++)
    {
        temp_a[k] = ((proximityForce[k] / this->proximityCount) - dragForce[k] + targetForce[k]) / this->mass;
        temp_v[k] = this->v.back()[k] + temp_a[k] * dt;
        temp_x[k] = this->x.back()[k] + this->v.back()[k] * dt;
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
        std::vector<float> r = this->getR(drn);
        float dist = this->getDistance(r);
        if (dist < this->proximityCaution)
        {
            for (int k = 0; k < 2; k++)
            {
                reqForce[k] = r[k] * this->proximityCoeff / dist;
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
    for (int k = 0; k < 2; k++)
    {
        dragForce[k] = pow(this->getV()[k], 2) * 0.5 * this->rho * this->S * this->C_D;
    }
    return dragForce;
}

std::vector<float> Drone::calculateTargetForce()
{
    std::vector<float> targetForce(2), dist(2);
    for (int k = 0; k < 2; k++)
    {
        dist[k] = this->goToLocation[k] - this->getX()[k];
        targetForce[k] = dist[k] * this->targetCoeff;
    }
    return targetForce;
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
    for (int k = 0; k < 2; k++)
    {
        this->requiredForce[k] += reqForce[k];
    }
    //this->addRequiredForce(reqForce);
    this->increaseProximityCount();
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
    dist = sqrt(dist);
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