#include "Fileloader.h"
int Fileloader::LoadFile(const std::string filename)
{
	std::ifstream operatedfile(filename);
	if (!operatedfile.is_open())
	{
		std::cerr << "File failed to open" << std::endl;
		return 1; //file not found
	}

	std::cout << "Reading file..." << std::endl;
	operatedfile >> size;
	array = new int[size];

	for (int i = 0; i < size; i++)
	{
		if (!(operatedfile >> array[i]))
		{
			std::cerr << "Error reading value at index " << i << std::endl;
			delete[] array;
			array = nullptr;
			size = 0;
			return 2; //error reading value
		}
	}

	return 0;
}

int Fileloader::SaveToFile(const std::string& filename) const
{
	if (array == nullptr || size == 0)
	{
		std::cerr << "Nothing to save. Array is empty or not loaded." << std::endl;
		return 1;
	}

	std::ofstream outfile(filename);
	if (!outfile.is_open())
	{
		std::cerr << "Failed to open file for writing: " << filename << std::endl;
		return 2;
	}

	// Write the size first
	outfile << size << std::endl;

	// Write array values, one per line
	for (int i = 0; i < size; i++)
	{
		outfile << array[i] << std::endl;
	}

	std::cout << "Array saved to: " << filename << std::endl;
	return 0;
}

void Fileloader::DisplayArray() const
{
	if (array == nullptr || size == 0)
	{
		std::cout << "Array is empty or not loaded." << std::endl;
		return;
	}

	std::cout << "Array contents:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}
