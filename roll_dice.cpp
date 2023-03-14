/*

When rolling a die, every face has the same probability.
But what is the advantage of rolling multiple dice and taking the maximum of all of them?

This problem was inspired by the video "The unexpected logic behind rolling multiple dice and picking the highest."
by the YouTube channel "Stand-up Maths" (https://www.youtube.com/watch?v=X_DdGRjtwAo)
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int rollDie(int die_max)
{
    int roll_result;
    int die_min = 1; 
    //int die_max = 20;

    roll_result = rand() % (die_max - die_min + 1) + die_min;

    return roll_result;
}

int find_max(int a1, int a2, int a3)
{
    int the_max = 0;  // the largest of the 3
    if(a1 >= a2 && a1 >= a3)  // check if the first one is the max
        the_max = a1;
    if(a2 >= a1 && a2 >= a3)  // the second
        the_max = a2;
    if(a3 >= a1 && a3 >= a2)  // the third
        the_max = a3;
    return the_max;
}


int main()
{
    srand(time(0));
    int max_times = 1e7;
    int max_value;  // for every roll
    int min_die_faces = 6; // start with dice with 6 faces
    int max_die_faces = 20; // end with dice with 20 faces
    ofstream out_dicefile("dice_expected_values.csv");    // file to save results
    
    //prepare for output
    cout << " f" << " " // faces
     << setw(15) << setfill(' ') << "2 dice " // 
     << setw(15) << setfill(' ') << "Analytical(2) " // "analytical" solution
     << setw(15) << setfill(' ') << "Advantage(2) " // 
     << setw(10) << setfill(' ') << "3 dice" << " " // advantage
     << setw(15) << setfill(' ') << "Advantage(3) " // 
     << setw(15) << setfill(' ')
    << endl;

    for (int faces_in_die = min_die_faces; faces_in_die<(max_die_faces+1); faces_in_die++)
        {
            double max_value_tot[2] = {};   // sum of the maximum of the two die rolls. To be divided by the n of repetitions
            for(int i=0;i<max_times;i++)   // repetitions
            {
                int roll1 = rollDie(faces_in_die);
                int roll2 = rollDie(faces_in_die);
                int roll3 = rollDie(faces_in_die);
                max_value_tot[0] += (double)max(roll1,roll2); // best of two
                max_value_tot[1] += find_max(roll1,roll2,roll3); // best of three
            }
            double expecetd_with_1_roll = (double)faces_in_die/2.0;  // expected value if I only rolled 1 die
            max_value_tot[0] = max_value_tot[0]/(double)max_times;  // expected value if I roll multiple times and take the max
            max_value_tot[1] = max_value_tot[1]/(double)max_times;  // expected value if I roll multiple times and take the max
            
            // save: n of faces, expected value rolling multiple times, increase in expected value, normalised increase 
            cout << setw(2) << setfill('0') << faces_in_die << " " // [1] pad with zeros
             //   2 dice
            << setw(13) << setfill(' ') << max_value_tot[0] << " "  // [2]
            << setw(13) << setfill(' ') << (double)((faces_in_die+1)*(4*faces_in_die-1))/(double)(faces_in_die)/6.0 << " " // "analytical" solution, (n+1)(4n-1)/n
            << setw(13) << setfill(' ') << max_value_tot[0] - expecetd_with_1_roll << " " // advantage with 2 dice
            << setw(13) << setfill(' ') << max_value_tot[1] << " " // 3 dice
            << setw(13) << setfill(' ') << max_value_tot[1] - expecetd_with_1_roll << " " //  advantage with 3 dice
            << endl;
            // print to file
            out_dicefile << faces_in_die << " " << max_value_tot[0] << " " << max_value_tot[0] - expecetd_with_1_roll << endl;
        }
}