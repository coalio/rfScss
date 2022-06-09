#pragma once
#include "state.h"
#include "debug.h"

class Parser {
private:
    // The state of the parser
    std::unique_ptr<State>& state;
public:
    // Creates a new Parser instance fed by a State instance
    Parser(std::unique_ptr<State>& _state) : state(_state) {
        LOG("Creating new parser using state: " << _state->curr_pos);
    }

    int8_t check_char(char c);

    // Moves to the next char. This also increments the current
    // char cursor. Does not deal with lines/columns counters
    void next(char c);
    // Updates the line and column
    void increment_cursor();
    // Manages the state when inside a comment
    // Principally, waits for the comment closing marker
    void in_comment();
    // Checks if there is a comment marker
    // If found, sets state->in_comment to true
    void find_comment_marker();
    // Checks if we're entering a rule or selector at the root level (0)
    // Usually after a closing brace. Does not check for levels above 0
    bool is_rule_or_selector();
    // Checks if the current character is valid in this context
    bool is_expected_char();
    // Checks if the current character is an opening brace
    bool is_opening_brace();
    // When capturing the selector, pushes the character to the last selector
    // in the state->selectors vector
    void push_to_selector();
    // Updates and returns the current capture level. Levels are updated
    // based in the brace count
    int check_capture_level();
    // When parsing finishes, this function checks for possible errors
    // If any were found, creates a new Error and saves it to state->error
    // for it to be read at main.cpp
    bool check_parsing_errors();

    void parse_input(
        std::string workspace,
        std::string input
    );
};