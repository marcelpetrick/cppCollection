# Problem to check

How to serialize a custom class (struct) via QSettings. Especially if the class contains a container of some other custom-class.

Of course, the literature and stackoverflow-articles dealing with this topic are existing. But nowhere I've found a valid solution.
Nor could I provide in 2 hours some working example.

layout more or less like this:

class Param
{ int avg; double exp; }

class DataSet
{ bool flag; std::vector<Param> params; }

as special topping maybe:
std::map<std::string, DataSet> entries; ..
