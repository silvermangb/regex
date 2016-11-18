/*
 * myregex.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: silve
 */

#include <iostream>
#include <vector>
#include <string>

char const star = '*';
char const dot  = '.';

bool
myregex
  (char const *  p_pattern,
   char const *  p_string)
{
	bool eot = false;
	while(!eot)
	{
		if(*p_pattern==star)
		{
			if(!*p_string)
			{
				return false;
			}
			while(*(p_string+1))
			{
				if(*p_string==*(p_string+1))
				{
					++p_string;
				}
				else
				{
					break;
				}
			}
			bool p_string_eos = *(p_string+1)==0;
			bool p_pattern_eos = *(p_pattern+1)==0;
			bool v = (p_string_eos&&p_pattern_eos) || !(p_string_eos||p_pattern_eos);
			switch(v)
			{
			case true:
				if(!p_string_eos)
				{
					++p_string;
					++p_pattern;
				}
				else
				{
					eot = true;
				}
				break;
			case false:
				return false;
				break;
			default:
				;
			}
		}
		else
		if(*p_pattern==dot)
		{
			if(*p_string==0)
			{
				return false;
			}
			else
			{
				++p_pattern;
				++p_string;
				eot = *p_pattern==0 && *p_string==0;
			}
		}
		else
		{
			if(*p_pattern==*p_string)
			{
				++p_pattern;
				++p_string;
				eot = *p_pattern==0 && *p_string==0;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

int
main
  ()
{
	std::cout << std::boolalpha;
	std::vector<std::string> test_patterns;
	std::vector<std::string> test_strings;

	test_patterns.push_back("");
	test_patterns.push_back(".*");
	test_patterns.push_back("*.");
	test_patterns.push_back("a*.");

	test_strings.push_back("");
	test_strings.push_back("abb");
	test_strings.push_back("aabc");
	test_strings.push_back("aab");
	test_strings.push_back("aaab");

	std::vector<std::pair<std::string,std::string> > trues;
	std::vector<std::pair<std::string,std::string> > falses;

	for(size_t i=0;i<test_patterns.size();++i)
	{
		for(size_t j=0;j<test_strings.size();++j)
		{

			bool v =  myregex(test_patterns[i].c_str(),test_strings[j].c_str());

			std::pair<std::string,std::string> t(test_patterns[i],test_strings[j]);
			if(v)
			{
				trues.push_back(t);
			}
			else
			{
				falses.push_back(t);
			}
		}
	}
	std::cout << "\n-------\ntrues:\n";
	for(size_t i=0;i<trues.size();++i)
	{
		std::cout << trues[i].first << ",\t" << trues[i].second << std::endl;
	}
	std::cout << "\n-------\falses:\n";
	for(size_t i=0;i<falses.size();++i)
	{
		std::cout << falses[i].first << ",\t" << falses[i].second << std::endl;
	}
	return 0;
}

