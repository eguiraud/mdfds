#ifndef PUNTO
#define PUNTO

/// \brief General utility to reinterpret the memory associated to a certain value
///  pun_to allows to reinterpret the memory associated to a variable without copies.
template <typename T, typename U>
const T &pun_to(const U &x)
{
   return *reinterpret_cast<const T *>(&x);
}

#endif //PUNTO