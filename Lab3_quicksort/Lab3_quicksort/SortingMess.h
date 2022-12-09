#pragma once

template <typename T, typename Compare>
void insertionSort(T* first, T* last, Compare comp) {
	for (T* i = first; i <= last; i++) {
		T* j = i - 1;
		T value = *i;
		while (j >= first && comp(value, *j)) {
			*(j + 1) = std::move(*j);
			j--;
		}
		*(j + 1) = value;
	}
}

template <typename T, typename Compare>
T PivotSearch(T& a, T& b, T& c, Compare compare) {
	if ((compare(a, b) && compare(c, a)) || (compare(a, c) && compare(b, a)))
		return a; 
	else if ((compare(b, a) && compare(c, b)) || (compare(b, c) && compare(a, b)))
		return b;
	else
		return c;
}

template <typename T, typename Compare>
void QuickSort(T* first, T* last, Compare compare) {
	while (first < last) {
		T pivot = PivotSearch(*first, *(first + (last - first) / 2), *last, compare);
		T* firsst = first;
		T* lasst = last;

		while (firsst <= lasst) {
			while (compare(*firsst, pivot))
				firsst++;

			while (compare(pivot, *lasst))
				lasst--;

			if (firsst <= lasst) {
				std::swap(*firsst, *lasst);
				firsst++;
				lasst--;
			}
		}

		if (last - lasst > lasst - first) {
			QuickSort(first, lasst, compare);
			first = lasst + 1;
		}
		else {
			QuickSort(lasst + 1, last, compare);
			last = lasst;
		}
	}
}

template<typename T, typename Compare>
void QuickSortWithInsert(T* first, T* last, Compare comp){
	if (last - first < 10) {
		insertionSort(first, last, comp);
		return;
	}
	else {
		QuickSort(first, last, comp);
		return;
	}
	
}
