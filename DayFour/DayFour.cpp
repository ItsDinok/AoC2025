#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// I am not happy with my solution for task two as it has dense logic and a disturbing logic error

void parse_input(const std::string& filename, std::vector<std::string>& input)
{
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		input.push_back(line);
	}
}

bool check_top_adjacent(int row, int index, const std::vector<std::string>& input)
{
	int adjacent = 0;
	// Check wall cases
	if (index == 0 || index == input.size() - 1) return true;
	
	if (row == 0) 
	{
		if (input[row][index - 1] == '@') ++adjacent;
		if (input[row][index + 1] == '@') ++adjacent;
		if (input[row + 1][index - 1] == '@') ++adjacent;
		if (input[row + 1][index] == '@') ++adjacent;
		if (input[row + 1][index + 1] == '@') ++adjacent;
	}
	else
	{
		if (input[row][index - 1] == '@') ++adjacent;
		if (input[row][index + 1] == '@') ++adjacent;
		if (input[row - 1][index - 1] == '@') ++adjacent;
		if (input[row - 1][index] == '@') ++adjacent;
		if (input[row - 1][index + 1] == '@') ++adjacent;
	}

	return adjacent < 4;
}

bool check_adjacent(int row, int index, const std::vector<std::string>& input)
{
	int adjacent = 0;
	// Check wall cases
	if (index == 0)
	{
		if (input[row - 1][index] == '@') ++adjacent;
		if (input[row - 1][index + 1] == '@') ++adjacent;
		if (input[row + 1][index] == '@') ++adjacent;
		if (input[row + 1][index + 1] == '@') ++adjacent;
		if (input[row][index + 1] == '@') ++adjacent;
	}
	else if (index == input[0].size() - 1)
	{
		if (input[row - 1][index] == '@') ++adjacent;
		if (input[row - 1][index - 1] == '@') ++adjacent;
		if (input[row + 1][index] == '@') ++adjacent;
		if (input[row + 1][index - 1] == '@') ++adjacent;
		if (input[row][index - 1] == '@') ++adjacent;
	}
	else 
	{
		if (input[row - 1][index - 1] == '@') ++adjacent;
		if (input[row - 1][index] == '@') ++adjacent;
		if (input[row - 1][index + 1] == '@') ++adjacent;
		if (input[row][index - 1] == '@') ++adjacent;
		if (input[row][index + 1] == '@') ++adjacent;		
		if (input[row + 1][index - 1] == '@') ++adjacent;
		if (input[row + 1][index] == '@') ++adjacent;
		if (input[row + 1][index + 1] == '@') ++adjacent;}

	return adjacent < 4;
}

// Count how many rolls of paper are accessible
// A roll of paper is accessible if it is touched by fewer than four other rolls
int task_one()
{
	// Get puzzle input
	std::vector<std::string> input;
	parse_input("DayFour.txt", input);

	int rolls = 0;

	// Iterate through all positions
	// Game of life check, essentially
	for (int i = 0; i < input.size(); ++i)
	{
		std::string row;
		for (int j = 0; j < input[0].size(); ++j)
		{
			row = input[i];
			if (row[j] == '.') continue;

			bool is_collectable;
			if (i == 0 || i == input.size() - 1)
			{
				is_collectable = check_top_adjacent(i, j, input);
			}
			else
			{
				is_collectable = check_adjacent(i, j, input);
			}

			if (is_collectable) ++rolls;
		}
	}

	return rolls;
}

// Task two is to count the number of paper rolls that can be accessed if accessible ones are removed
int task_two()
{
	// Get puzzle input
	std::vector<std::string> input;
	parse_input("DayFour.txt", input);

	int rolls = 0;
	// The removal has to be done in place
	std::vector<std::string> in_place = input;
	int old_x = -1;

	while (true) 
	{
		int x_count = 0;
		for (int i = 0; i < input.size(); ++i)
		{
			std::string row;
			row = input[i];
			for (int j = 0; j < input[0].size(); ++j)
			{
				if (row[j] == '.') continue;

				bool is_collectable;
				if (i == 0 || i == input.size() - 1)
				{
					is_collectable = check_top_adjacent(i, j, input);
				}
				else
				{
					is_collectable = check_adjacent(i, j, input);
				}

				if (is_collectable)
				{
					++x_count;
					in_place[i][j] = 'x';
				}
			}
		}

		std::cout << "X count: " << x_count << std::endl;
		std::cout << "Rolls:  " << rolls << std::endl;

		// No activity
		if (x_count == old_x) break;

		old_x = x_count;
		input = in_place;
		rolls = x_count;
		x_count = 0;
	}

	return rolls;
}

int main()
{
	int result_one = task_one();
	std::cout << "Result one: " << result_one << std::endl;
	int result_two = task_two();
	std::cout << "Result two: " << result_two << std::endl;
	return 0;
}
