// 3307Parsing.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include "PresentationCsvParser.h"

int main()
{
	PresentationCsvParser parser;
	parser.parse("testfile.csv");
    return 0;
}

