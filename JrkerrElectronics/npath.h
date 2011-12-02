#ifndef NPATH_H
#define NPATH_H

#include <QList>
#include <QVector>

typedef QVector<double> State;

class NPath
{
public:
    NPath();
    /**
     * Constructor for an NPath, the machines state space will be of size n.
     * 0 will be the time coordinate, all other coordinates will be for states 1->N
     */
    NPath(int n);

    NPath(int n, bool isRelative);

    void setAllStates(bool all);

    void setStateSize(int n);

    /**
     * Returns the machines state space size.
     */
    int stateSize();
    /**
     * Addes a vector to the list of machine states.
     * if the added vector is not of the correct size
     * it will return false and not add the vector
     */
    bool addState(QVector<double>);
    /**
     * Returns the stateVector at index i if i<=states_.size()
     * Returns a null vector if i>states_.size()
     */
    QVector<double> getState(int i);

    bool setState(int i, State new_state);

    int numberOfStates();

    void clear();

    void toRelative();
    void toAbsolute();
    void shift(State shiftby);

    void setOrigin(State origin);
    State origin();
    State lastAbsolute();

private:
    QVector<QVector<double> > states_;
    int state_size_;
    bool isRelative_;
    State origin_;
    bool allStates_;

};

State subStates(State s1, State s2, bool allStates);
State addStates(State s1, State s2, bool allStates);

#endif // NPATH_H
