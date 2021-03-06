#include "clar.h"
#include <ssm.h>

static int parameters_length; 
static int states_length; 
static ssm_parameter_t **parameters;
static ssm_state_t **states;

void test_states__initialize(void)
{
    parameters = _ssm_parameters_new(&parameters_length);
    states = _ssm_states_new(&states_length, parameters);
}

void test_states__cleanup(void)
{
    int i;
    for(i=0; i<parameters_length; i++){
        _ssm_parameter_free(parameters[i]);
    }
    free(parameters);

    for(i=0; i<states_length; i++){
        _ssm_state_free(states[i]);
    }
    free(states);
}

void test_states__states_new(void)
{    
    int i;
    char *expected_names[] = {"I_nyc", "I_paris", "S_nyc", "S_paris", "Inc_in_nyc", "Inc_out", "r0_nyc", "r0_paris", "R_nyc", "R_paris"};
    char *expected_ic_names[] = {"pr_I_nyc", "pr_I_paris", "S_nyc", "pr_S_paris", "Inc_in_nyc", "Inc_out", "r0_nyc", "r0_paris", "R_nyc", "R_paris"};
    int expected_offsets[] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1};

    cl_check(states_length == sizeof(expected_names)/sizeof(*expected_names));
    for(i=0; i<states_length; i++){
	cl_assert(states[i]->offset == expected_offsets[i]);
	cl_assert_equal_s(states[i]->name, expected_names[i]);
	if(states[i]->ic){
	    cl_assert_equal_s(states[i]->ic->name, expected_ic_names[i]);
	}
    }
}
