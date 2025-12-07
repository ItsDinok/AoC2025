#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

void parse_input(const std::string& filename, std::vector<std::string>& input)
{
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		input.push_back(line);
	}
}

// Within each bank two batteries need to be turned on
// These need to concatenate to produce the largest possible result
// Batteries cannot be reordered
int task_one()
{
	std::vector<std::string> input;
	parse_input("DayThree.txt", input);
	int sum_total = 0;

	// Loop through all battery banks
	std::string bank;
	for (int i = 0; i < input.size(); ++i)
	{
		bank = input[i];

		// Pass to find highest value and index
		// Last digit is skipped this pass because it cannot be used
		int highest_index = 0;
		char highest_value = bank[0];
	
		for (int j = 1; j < bank.size()-1; ++j)
		{
			if (bank[j] > highest_value)
			{
				highest_index = j;
				highest_value = bank[j];
			}
		}

		// Get second digit
		int s_highest_index = highest_index + 1;
		int s_highest_value = bank[s_highest_index];
		for (int j = highest_index + 1; j < bank.size(); ++j)
		{
			if (bank[j] > s_highest_value)
			{
				s_highest_index = j;
				s_highest_value = bank[j];
			}
		}

		// Concatenate and add
		std::string to_convert;
		to_convert += highest_value;
		to_convert += s_highest_value;
		sum_total += std::stoi(to_convert);
	}

	return sum_total;
}

char check_range(const std::string& input, int& start, int end)
{
	char highest_value = input[start];

	for (int i = start; i < end; ++i)
	{
		if (input[i] > highest_value)
		{
			highest_value = input[i];
			start = i;
		}
	}

	return highest_value;
}

// For this task twelve batteries must be turned on in every bank
uint64_t task_two()
{
	std::vector<std::string> input;
	parse_input("DayThree.txt", input);
	uint64_t sum_total = 0;

	// Loop through all battery banks
	std::string bank;
	for (int i = 0; i < input.size(); ++i)
	{
		bank = input[i];
	
		// Used to automate process in task one
		int start = 0;
		int end = bank.size() - 11;
		
		// Iteratively find the next highest digit
		std::string joltage = "";
		for (int j = 0; j < 12; j++)
		{
			joltage += check_range(bank, start, end);
			++start;
			++end;
		}

		sum_total += std::stoull(joltage);
	}

	return sum_total;
}

int main()
{
	int result_one = task_one();
	std::cout << "Result one: " << result_one << std::endl;
	uint64_t result_two = task_two();
	std::cout << "Result two: " << result_two << std::endl;

	return 0;
}
