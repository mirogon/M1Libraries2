#pragma once
#include <string>
#include <vector>
#include <fstream>

namespace m1
{

	class M1Config
	{
	public:

		bool read_value(const std::string& filename, const std::string& value_name, std::string& value);

		bool read_value_list(const std::string& filename, const std::string& value_name, std::vector<std::string>& list);

	};


	inline bool M1Config::read_value(const std::string& filename, const std::string& value_name, std::string& value)
	{
		std::ifstream input_stream(filename.c_str(), std::ios::in);

		if (!input_stream.good())
		{
			return false;
		}

		char c;

		std::string current_read;

		bool found_value = false;

		while (input_stream.get(c))
		{
			if (c == ':')
			{
				if (current_read == value_name)
				{
					found_value = true;
				}
				current_read.clear();
				current_read.shrink_to_fit();
				continue;
			}


			else if (c == ';')
			{
				if (found_value)
				{
					value = current_read;
					input_stream.close();
					return true;
				}
				current_read.clear();
				current_read.shrink_to_fit();
				continue;
			}

			if (!found_value)
			{
				if (c == ' '  /*|| c < 48 || c > 122 || (c > 57 && c < 65) || (c > 90 && c < 97)*/)
				{
					continue;
				}
				else if (c == '\n')
				{
					current_read.clear();
					current_read.shrink_to_fit();
					continue;
				}
			}

			current_read.push_back(c);
		}

		input_stream.close();

		return false;
	}

	inline bool M1Config::read_value_list(const std::string& filename, const std::string& value_name, std::vector<std::string>& value_list)
	{
		std::ifstream input_stream(filename.c_str(), std::ios::in);

		if (!input_stream.good())
		{
			return false;
		}

		char c;

		std::string current_read;

		bool found_value = false;

		while (input_stream.get(c))
		{
			if (c == ':')
			{
				if (current_read == value_name)
				{
					found_value = true;
				}
				current_read.clear();
				current_read.shrink_to_fit();
				continue;
			}

			else if (c == ';' || c == ',')
			{
				if (found_value)
				{
					value_list.push_back(current_read);
					if (c == ';')
					{
						input_stream.close();
						return true;
					}
				}
				current_read.clear();
				current_read.shrink_to_fit();
				continue;
			}

			if (!found_value)
			{
				if (c == ' ' || c == '\n' /* || c < 48 || c > 122 || (c > 57 && c < 65) || (c > 90 && c < 97)*/)
				{
					continue;
				}
			}

			current_read.push_back(c);
		}

		input_stream.close();

		return false;
	}

}