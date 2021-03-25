//Turing Machine Simulator 
/*
    This program simulates a one-track, two-way, infinite tape
    deterministic Turing Machine.
    it asks for a file name, which contains the “code” of the TM
    as input, then asks for an input word and outputs the sequence 
    of IDs that the TM goes through on that input. When it gets to 
    a final state it clearly indicates that the string was accepted. 
    If it gets to any other state, symbol pair with no transition it 
    stops computing and indicates the string was not accepted. If 
    looping, the TM is stoppable by a choice of input without 
    crashing the simulator. 
    After any case, the user id prompted to run the TM on another input 
    string.
    The input file consists of multiple lines. Each line is either blank, 
    a comment indicated by “//” or a 5-tuple consisting of currentState 
    currentTapeSymbol newState newTapeSymbol direction, followed by an 
    optional comment, also indicated by “//”. States are indicated by either 
    an integer (with 0 representing the start state q0) or the letter f for 
    Final state. Σ = {0, 1} 
*/


#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <iostream>

using namespace std;

vector<vector<string>> turingStateBuilder(const string &filename_)
{
    string read_string_;
    ifstream file_(filename_);
    vector<vector<string>> states_;
    string states_list_;
    int iterator_ = 0;
    int next_ = 0;
    
    if (file_.is_open())
    {
        while ( getline (file_, read_string_) )
        {      
            bool seen = false;
            if ( (read_string_[0] != '/') && (read_string_ != "") )
            {

                //cout << read_string_ << endl;

                for (size_t i = 0; i < states_list_.size(); i++)
                {
                    if (read_string_[0] == states_list_[i])
                    {
                        seen = true;
                        iterator_ = i;
                    }
                }

                if (seen == false)
                {
                    states_list_ += read_string_[0];
                    string temp_state_;
                    for (size_t i = 0; i < 9; i+=2)
                    {
                        temp_state_ += read_string_[i]; 
                    }                  
                    vector<string> temp_vect_ = {temp_state_};
                    states_.push_back(temp_vect_);
                }

                else
                {
                    string temp_state_;
                    for (size_t i = 0; i < 9; i+=2)
                    {
                        temp_state_ += read_string_[i];
                    }
                    
                    states_[iterator_].push_back(temp_state_);
                    iterator_ = 0;
                }
                
            }

        }
        
        file_.close();
        return states_;
    }
    else 
    {
      cout << "Unable to open file" << endl;
    }

}

//gets the list of states in the same order as the vector
string turingStateList(vector<vector<string>> states_)
{
    string list_;
    for (size_t i = 0; i < states_.size(); i++)
    {
        list_ += states_[i][0];
    }
    
    return list_;
}

int checkTransition(vector<string> state_rules_, char current_item_)
{
    for (size_t i = 0; i < state_rules_.size(); i++)
    {
        char transition_ = state_rules_[i][1];
        
        if ( transition_ == current_item_)
            {
                return i;
            }
    }
    return -1;
}

string tapeOutput(string tape_, int state_, int place_)
{
    string return_tape_;
    string state_string_ = "-q";
    state_string_ += to_string(state_);
    state_string_ += "-";
    if (place_ == 0)
    {
        return_tape_ = state_string_ + tape_;
        return return_tape_;
    }
    else
    {
        string tape_first_ = tape_.substr(0, place_);
        string tape_second_ = tape_.substr(place_);
        return_tape_ = tape_first_ + state_string_ + tape_second_;
        return return_tape_;
    }
    
}



void turingMachine(const string &turing_file_, const string &test_word_)
{
    vector<vector<string>> turing_states_ = turingStateBuilder(turing_file_);

    //adds blanks to both ends of the tape
    string tape_ = 'B' + test_word_ + 'B';

    int curr_tape_place_ = 1;
    int curr_state_ = 0;
    int next_state_ = 0;
    bool run = true;    
 
    while (run)
    {   
        cout << tapeOutput(tape_, curr_state_, curr_tape_place_) << endl;

       int found_line_ = checkTransition(turing_states_[curr_state_], tape_[curr_tape_place_]);
       if (found_line_ == -1)
       {
           cout << "String not accepted" << endl;
           run = false;
       }
       else
       {   
            if (turing_states_[curr_state_][found_line_][2] == 'f')
            {
                cout << "Word is Accepted" << endl;
                run = false;
            }
            else
            {

                 char temp_string_ = turing_states_[curr_state_][found_line_][2];
                 next_state_ = int(temp_string_) - int('0');
                 tape_[curr_tape_place_] = turing_states_[curr_state_][found_line_][3];

                 char direction_ = turing_states_[curr_state_][found_line_][4];
                 if (direction_ == 'R')
                 {
                     curr_tape_place_++;
                 }
                 else
                 {
                     curr_tape_place_ -= 1;
                 }

                 curr_state_ = next_state_;
            }
       }
    }
}

int main()
{
    string test_file_;
    cout << "enter file name:" << endl;
    cin >>  test_file_;
    
    bool loop = true;

    while (loop)
    {
        string word_;
        cout << "enter word:" << endl;
        cin >> word_;
        turingMachine(test_file_, word_);
        cout << "press ctrl+c to exit the program" << endl << "or ";
    }

    return 0;
}
