//! Sum all values in the container.
auto const progressMaximum = std::accumulate(input.begin(), input.end(), 0);

//! Rename the key of some entry in a std::map. (C++17)
std::map<std::string, int> entries;
auto node = entries.extract(oldName);
node.key() = newName; // explodes here, because std::string does not like to be touched
entries.insert(std::move(node));
