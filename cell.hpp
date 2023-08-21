#ifndef CELL_HPP
#define CELL_HPP

enum class State{Susceptible, Infected, Removed, Void};

class Cell{
    private:
    State m_state{};

    public:
    Cell();
    Cell(State);

    State get_state() const; //ritorna lo stato di una cella
    void set_state(State new_state); //assegna il nuovo stato a una cella
};

#endif