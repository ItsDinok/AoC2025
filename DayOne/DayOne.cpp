#include <iostream>
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

// This task simulates a safe dial, with the target being to determine how many moves
// end on a zero
int task_one(std::vector<std::string>& input)
{
	int zeroes = 0;
	int position = 50;
	
	// Iterate through all lines and decipher what they are
	for (size_t i = 0; i < input.size(); ++i)
	{
		std::string line = input[i];
		bool is_right;

		// Check direction
		if (line[0] == 'L') is_right = false;
		else is_right = true;

		// Get number component
		line.erase(0, 1);
		int rotation = std::stoi(line);

		// Move dial
		if (is_right)
		{
			position = (position + rotation) % 100;
		}
		else
		{
			position = (position - rotation + 100) % 100;
		}
		if (position == 0) ++zeroes;
	}
	return zeroes;
}

// Task two simulates the same dial, but asks how many times zero is hit, even mid-turn
int task_two(std::vector<std::string>& input)
{
	int zeroes = 0;
	int position = 50;
	std::string line;

	// Very naive method but negative mod hurts my head
	for (size_t i = 0; i < input.size(); ++i)
	{
		bool is_right;
		line = input[i];
		
		if (line[0] == 'L') is_right = false;
		else is_right = true;
		line.erase(0, 1);
		int rotation = std::stoi(line);
		
		if (is_right)
		{
			for (int j = 0; j < rotation; ++j)
			{
				if (position == 0) ++zeroes;
				++position;
				if (position > 99) position = 0;
			}
		}
		else 
		{
			for (int j = 0; j < rotation; ++j)
			{
				if (position == 0) ++zeroes;
				--position;
				if (position < 0) position = 99;
			}
		}
	}
	return zeroes;
}

int main()
{
	std::vector<std::string> puzzle_input;
	parse_input("DayOne.txt", puzzle_input);

	int result = task_one(puzzle_input);
	std::cout << "Task one result: " << result << std::endl;

	int result_two = task_two(puzzle_input);
	std::cout << "Task two result: " << result_two << std::endl;

	return 0;
}
