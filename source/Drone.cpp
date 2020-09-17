Drone::Drone(float mass, std::vector<float> x_initial, std::vector<float> v_initial)
{
    this->mass = mass;
    this->x.push_back(x_initial);
    this->v.push_back(v_initial);
}

Drone::~Drone()
{
}

void Drone::applyForce(std::vector<float> force, float dt)
{
    std::vector<float> temp_a, temp_v, temp_x;
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

void Drone::notifyAll()
{
    if (this->isChanged)
    {
        for (auto it = this->_observers.begin(); it != this->_observers.end(); ++it)
        {
            (*it)->update();
        }
        this->isChanged = false;
    }
}

void Drone::setChanged()
{
    this->isChanged = true;
}

void Drone::check()
{
    while (true)
    {
    }
}

