#include <iostream>
#include <vector>

#include "testlib.h"

/**
 * Description:
 * 
 * In this kata, you will write a function that returns the positions and the values of the "peaks" (or local maxima) of a numeric array.
 * For example, the array arr = [0, 1, 2, 5, 1, 0] has a peak at position 3 with a value of 5 (since arr[3] equals 5).
 * The output will be returned as an object of type PeakData which has two members: pos and peaks.
 * Both of these members should be vector<int>s.
 * If there is no peak in the given array then the output should be a PeakData
 * with an empty vector for both the pos and peaks members.
 *  PeakData is defined in Preloaded as follows:
 * 
 * struct PeakData {
 *   vector<int> pos, peaks;
 * };
 * 
 * Example: pickPeaks([3, 2, 3, 6, 4, 1, 2, 3, 2, 1, 2, 3]) should return
 * {pos: [3, 7], peaks: [6, 3]} (or equivalent in other languages)
 * All input arrays will be valid integer arrays (although it could still be empty), so you won't need to validate the input.
 * The first and last elements of the array will not be considered as peaks
 * (in the context of a mathematical function,
 * we don't know what is after and before and therefore, we don't know if it is a peak or not).
 * Also, beware of plateaus !!! [1, 2, 2, 2, 1] has a peak while [1, 2, 2, 2, 3] and [1, 2, 2, 2, 2] do not.
 * In case of a plateau-peak, please only return the position and value of the beginning of the plateau.
 * For example: pickPeaks([1, 2, 2, 2, 1]) returns {pos: [1], peaks: [2]} (or equivalent in other languages)
 * Have fun!
*/

// https://www.codewars.com/kata/5279f6fe5ab7f447890006a7/train/cpp

struct PeakData
{
	std::vector<int> pos, peaks;
};

// not solve yet
PeakData pick_peaks(const std::vector<int> &v)
{
	bool keep_plato = false;
	int left = *v.begin(), right = 0, remember_begin_plato = 0;
	auto remember_begin = v.begin();
	PeakData pd;

	for (auto it = v.begin() + 1; it != v.end(); it++)
	{
		if (it + 1 != v.end())
			right = *(it + 1);
		else
			break;

		int mid = *it;

		if ((left < right) or (left > right))
		{
			if ((mid > left) and (mid > right))
			{
				if (((mid - left) >= 1) and ((mid - right) >= 1))
				{
					pd.peaks.push_back(mid);
					pd.pos.push_back(it - remember_begin);
					goto next;
				}
			}
		}
		if (not keep_plato)
		{
			if (((mid - left) == 0) and ((mid - right) == 0)) // it's "plato"
			{
				remember_begin_plato = (it - 1) - remember_begin;
				keep_plato = true;
			}
			if ((mid - left > 0) and (mid - right > 0)) // local peak, add to result vectors
			{
				pd.peaks.push_back(mid);
				pd.pos.push_back(it - remember_begin);
			}
		}
		else // its really "plato" ?
		{
			if ((mid - left) == 0 and (mid - right) > 0)
			{
				// normal exit from "plato"
				pd.peaks.push_back(mid);
				pd.pos.push_back(remember_begin_plato);
				keep_plato = false;
			}
			else if ((mid - left) == 0 and (mid - right) < 0)
			{
				auto past_left = v.begin() + remember_begin_plato;
				// check, that "plato" is reverse
				if (*past_left - *(past_left - 1) < 0)
				{
					pd.peaks.push_back(mid);
					pd.pos.push_back(remember_begin_plato);
				}
				else
				{
					// nothing, its not a "plato"
				}
				keep_plato = false;
			}
			else if ((mid - left > 0) and (mid - right > 0))
			{
				pd.peaks.push_back(mid);
				pd.pos.push_back(it - remember_begin);

				keep_plato = false;
			}
		}
next:
		left = *it;
	}
	return pd;
}

int main()
{
	std::vector<int> test_sequence_1 = {3, 2, 3, 6, 4, 1, 2, 3, 2, 1, 2, 3};
	PeakData res1 = pick_peaks(test_sequence_1);

	std::vector<int> expected_pos_1 = {3, 7}, expected_peaks_1 = {6, 3};
	IS_ARRS_EQUALS(res1.pos, expected_pos_1, 2);
	IS_ARRS_EQUALS(res1.peaks, expected_peaks_1, 2);

	std::vector<int> test_sequence_2 = {1, 2, 2, 2, 1};
	PeakData res2 = pick_peaks(test_sequence_2);

	std::vector<int> expected_pos_2 = {1}, expected_peaks_2 = {2};
	IS_ARRS_EQUALS(res2.pos, expected_pos_2, 2);
	IS_ARRS_EQUALS(res2.peaks, expected_peaks_2, 2);

	std::vector<int> test_sequence_3 = {1, 2, 2, 2, 3};
	PeakData res3 = pick_peaks(test_sequence_3);
	IS_EQUALS(res3.pos.empty(), true);
	IS_EQUALS(res3.peaks.empty(), true);

	// reverse plato
	std::vector<int> test_sequence_4 = {5, 2, 2, 2, 4};
	PeakData res4 = pick_peaks(test_sequence_4);

	std::vector<int> expected_pos_4 = {1}, expected_peaks_4 = {2};
	IS_ARRS_EQUALS(res4.pos, expected_pos_2, 1);
	IS_ARRS_EQUALS(res4.peaks, expected_peaks_2, 1);

	// maximum with reverse plato
	std::vector<int> test_sequence_5 = {5, 2, 2, 2, 4, 1, 1, 10, 1, 1, 4};
	std::vector<int> expected_pos_5 = {1, 6}, expected_peaks_5 = {2, 10};

	IS_ARRS_EQUALS(res4.pos, expected_pos_2, 2);
	IS_ARRS_EQUALS(res4.peaks, expected_peaks_2, 2);

	return EXIT_SUCCESS;
}