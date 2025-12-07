#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

using uint64_t = long long;

// This takes the input in
void parse_input(const std::string& filename, std::string& input)
{
	std::ifstream file(filename);
	std::string line;
	std::getline(file, line);
	input = line;
}

// This turns the string into the comma delineated vector of substrings
void turn_to_vector(std::string& input, std::vector<std::string>& output)
{
	// Delimited by commas
	std::string buffer = "";
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == ',')
		{
			output.push_back(buffer);
			buffer = "";
		}
		else
		{
			buffer += input[i];
		}
	}
	output.push_back(buffer);
}

// This gets the upper and lower bounds from a range xx-yy
void get_bounds(std::string& input, uint64_t& l_bound, uint64_t& u_bound)
{
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == '-')
		{
			l_bound = std::stoull(input.substr(0, i));
			u_bound = std::stoull(input.substr(i+1));
		}
	}
}

// The task is to sum 'iuint64_tegal ID's'
// Illegal ID's have repeating strings in them
uint64_t task_one(std::string& input)
{
	// Prepare data
	std::vector<std::string> range_list;
	turn_to_vector(input, range_list);
	std::vector<uint64_t> invalid_values;

	// Loop through vector
	for (int i = 0; i < range_list.size(); ++i)
	{
		uint64_t l_bound, u_bound;
		get_bounds(range_list[i], l_bound, u_bound);
		std::string tested;
		for (uint64_t j = l_bound; j < u_bound + 1; ++j)
		{
			tested = std::to_string(j);
			// Odd numbers cannot match the case
			if (tested.size() % 2 != 0) continue;

			// Check if it is two repeating halves
			if (tested.substr(0, tested.size()/2) == tested.substr(tested.size()/2))
			{
				invalid_values.push_back(j);
			}		
		}
	}
	return std::accumulate(invalid_values.begin(), invalid_values.end(), 0LL);
}

std::string generate_repeated(const std::string& stump, int size)
{
	std::string to_return = "";
	while (to_return.size() < size)	
	{
		to_return += stump;
	}
	return to_return;
}

// Invalid if the string is made of n repeating digits
uint64_t task_two(std::string& input)
{
	// Prepare data
	std::vector<std::string> range_list;
	turn_to_vector(input, range_list);
	std::vector<uint64_t> invalid_values;

	// Loop through vector
	for (int i = 0; i < range_list.size(); ++i)
	{
		// Get loop bounds
		uint64_t l_bound, u_bound;
		get_bounds(range_list[i], l_bound, u_bound);
		
		// Iterate through all values within range
		std::string tested;
		for (uint64_t j = l_bound; j < u_bound + 1; ++j)
		{
			tested = std::to_string(j);

			// Iterate through the string
			// Only need to check halfway
			for (int x = 1; x <= tested.size() / 2; ++x)
			{
				// Cannot be repeating from this value if the mod is != 0
				if (tested.size() % (x) != 0) continue;
		
				// Check to see if a constructed string with substr is equal
				std::string demo = generate_repeated(tested.substr(0, x), tested.size());
				if (demo == tested) 
				{
					invalid_values.push_back(j);
					break;
				}			
			}
		}
	}

	return std::accumulate(invalid_values.begin(), invalid_values.end(), 0LL);
}

int main()
{
	std::string input;
	parse_input("DayTwo.txt", input);

	uint64_t result_one = task_one(input);
	std::cout << "Task one: " << result_one << std::endl;
	uint64_t result_two = task_two(input);
	std::cout << "Task two: " << result_two << std::endl;

	return 0;
}
