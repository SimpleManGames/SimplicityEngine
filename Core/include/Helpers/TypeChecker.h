#ifndef _TYPECHECKER_H

namespace TypeChecker {
	template<typename T, typename U>
	struct is_same { static const bool value = false; };

	template<typename T>
	struct is_same<T, T> { static const bool value = true; };

	template<typename T, typename U>
	bool eqTypes() { return is_same<T, U>::value; }
}

#endif // !_TYPECHECKER_H
