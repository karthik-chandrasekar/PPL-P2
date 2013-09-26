#include <iostream>
#include <string>

using namespace std; 

int getInput();
void cleanInput(int);
void get_input_array(int, int, int, int);
void print_input_array(int);
int validateInput(int);
int validateTerminals(int);
int validateNonTerminals(int);

string grammar_array[100];
char input_array[100][100];

int main () 
{
	int count;
	int isValid;

	count = getInput();
	cleanInput(count);
	print_input_array(count); 
	isValid = validateInput(count);
	if (isValid == 0)
		cout << "Input is not valid"<<endl;
	return 0;
} 

int getInput()
{
//Get the input.

	string line;
	int i, count =0;
	cout << "Enter grammar specification"<<endl;
	while(true)
	{
		getline(cin, line);
		if (line.empty())
			break;
		grammar_array[count] = line;
		count++;	
	}

	for(i=0;i < count; i++)
	{	
		cout << "Grammar specification" << "  " <<grammar_array[i]<<endl;
	}
	return count;
}

void print_input_array(int count)
{
//Just print the array
	int i,j;
	for (i=0;i< count; i++)
	{
		for (j=0;;j++)
		{
			if (input_array[i][j] == '\0')
				break;
			cout<<"i "<<i<<"  "<<"j "<<j<<" "<<"value "<<input_array[i][j]<<" "<<endl;
		}
	}
}

void cleanInput(int count)
{
//Inputs can have multiple statements in a single statement separated by # and ## and the end of grammar. So properly put them in an array such that every single rule is separately stored. 

	int rows_count = count;
	int start_col;	
	int end_col = 0;
	int rule_count = 0;
	int i,j;

	for(i=0;i<rows_count;i++)
	{
		start_col =0;
		for(j=0;;j++)
		{
			if(grammar_array[i][j] == '#')   //If we encounter # it is end of a rule
			{
				end_col = j;
				get_input_array(i,start_col, end_col, rule_count);
				rule_count += 1;
				start_col = end_col;
				break;
			}
		}
	}
}


void get_input_array(int row, int start_col, int end_col, int rule_count)
{
	int i,j;
	for(i=start_col, j=0; i<end_col; i++,j++)
	{
		input_array[rule_count][j] = grammar_array[row][i];	
	}
}


int validateInput(int count)
{
// Validate whether the entered input is proper
	int isValidTerm;
	int isValidNonTerm;

   	isValidTerm = validateTerminals(count); 
	isValidNonTerm = validateNonTerminals(count);
	if (isValidTerm && isValidNonTerm)
		{
		return 1;
		}
	else
		{
		return 0;
		}
}

int validateTerminals(int count)
{
// Check if All terminals have some rule associated with it


	string terminals;
	int term = 0;
	int i, j, k;
	
	terminals = input_array[0];

	for(i=0;i<count;i++)
	{
		for(j=0,k=0;j<count;j++)
		{
			//cout<<"terminal "<<terminals[i]<<" "<<"Input "<<input_array[j][k]<<" "<<"index "<<"i "<<i <<"j "<<j<<"k "<<k<<endl;
			if (terminals[i] == input_array[j][k])
			   {		
				term = 1;
				break;
			   }
		}

		if(term ==0 )
			return 0;
	}
	return 1;
}

int validateNonTerminals(int count)
{
	string non_terminal;
	int non_term = 0;
	int i, j, k;

	non_terminal = input_array[1];
	
	for(i=0;i<count;i++)
	{
		for(j=0;j<count;j++)
		{
			for(k=0;;k++)
			{
				//cout<<"terminal "<<terminals[i]<<" "<<"Input "<<input_array[j][k]<<" "<<"index "<<"i "<<i <<"j "<<j<<"k "<<k<<endl;
				if (input_array[j][k] == '\0')
					break;
				if (non_terminal[i] == input_array[j][k])
				{
					non_term = 1;
					break;
				}
			}
		}
		if (non_term ==0)
			return 0;
	}
	return 1;
}

//Input getting part need to be revisited for sure. 
