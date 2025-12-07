#include <algorithm>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

// God forgive me for this line
#define long uint64_t

void allocate_range_values(const std::vector<std::string>& fresh_ranges,
		std::vector<std::pair<long, long>>& range_values)
{
	long left, right;
	
	// Iterate through each range
	for (int i = 0; i < fresh_ranges.size(); ++i)
	{
		// Iterate through the range in question
		for (int j = 0; j < fresh_ranges[i].size(); ++j)
		{
			if (fresh_ranges[i][j] == '-')
			{
				left = std::stoull(fresh_ranges[i].substr(0, j));
				right = std::stoull(fresh_ranges[i].substr(j + 1));
			}
		}

		range_values.push_back(std::make_pair(left, right));	
	}
}
// Slightly more complex txt parser
void parse_input(const std::string& filename, 
		std::vector<std::pair<long, long>>& f_ranges,
		std::vector<std::string>& indices)
{
	std::vector<std::string> fresh_ranges;
	std::ifstream file(filename);
	std::string line;
	bool is_blank = false;

	while (std::getline(file, line))
	{
		if (is_blank)
		{
			indices.push_back(line);
		}
		else if (line == "") is_blank = true;
		else
		{
			fresh_ranges.push_back(line);
		}
	}
	
	allocate_range_values(fresh_ranges, f_ranges);
}

// Ingredients are fresh if their index (stored in indices) appears in one or any of the
// provides ranges (fresh ranges). Return the total number of fresh ingredients
int task_one()
{
	// Load data
	std::vector<std::pair<long, long>> range_values;
	std::vector<std::string> indices;
	parse_input("DayFive.txt", range_values, indices);

	int freshes = 0;
	long value;

	// Check all indices
	for (int i = 0; i < indices.size(); ++i)
	{
		value = std::stoull(indices[i]);
		
		// Check against all ranges
		for (int j = 0; j < range_values.size(); ++j)
		{
			if (value >= range_values[j].first && value <= range_values[j].second)
			{
				++freshes;
				break;
			}
		}
	}

	return freshes;
}

// Task two is attempting to discover how many ID's are valid
long task_two()
{
	// Load data
	std::vector<std::pair<long, long>> range_values;
	std::vector<std::string> indices;
	parse_input("DayFive.txt", range_values, indices);

	// Sort vector by first id
	std::sort(range_values.begin(), range_values.end());
	
	// Check for overlap and merge
	int ptr = 0;
	while (ptr < range_values.size() - 1)
	{
		// There must be overlap
		if (range_values[ptr].second >= range_values[ptr + 1].first)
		{
			range_values[ptr].second = std::max(range_values[ptr].second,
												range_values[ptr + 1].second);
			range_values.erase(range_values.begin() + ptr + 1);
		}
		else ++ptr;
	}

	// Sum all ranges
	long valid_indices = 0;
	for (int i = 0; i < range_values.size(); ++i)
	{
		valid_indices += (range_values[i].second - range_values[i].first) + 1;
	}

	return valid_indices;
}

int main()
{
	int result_one = task_one();
	std::cout << "Result one: " << result_one << std::endl;
	long result_two = task_two();
	std::cout << "Result two: " << result_two << std::endl;

	return 0;
}
