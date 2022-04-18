# Project #1: Typing Game
### Scenario:
You are to create a typing game that can be played through the Cygwin terminal. Words will appear in a box and the player will need to type the words before they reach the bottom of the box or the game will end.
******
### Code Requirements:

- Use of the provided text file (on Canvas) to produce the words that are used in the game. 
  - The words that are used in the game should be randomly chosen and different for each instance of the game.
- Use of a 2D array for the playing board to keep track of the position of the words.
- Have the computer randomly choose the starting position of each word
  - It should pick its x position, the y position should always be at the top.
  - The word should always be contained in the board, for instance it should always have enough space to its right for its length.
- Prompt the user if they are ready to start at the beginning.
- Give them the option to add words to the text file you are using. The changes should persist between instances of the program.
- Have a way to check if the game has ended (i.e. if a word has reached the bottom of the board)
- The player should be able to type any word they want, not just the one that is closest to the bottom.
- The word must disappear from the next board and no longer affect the gamestate only after the user has typed the word correctly.
- The time of the player is recorded and displayed at the end.
- The words DON’T need to be generated without user input.
  - It would be very difficult to have words appear while the user can be typing in the console. So we will update and reprint the entire board after the user gives input.
  - The longer a user takes to type in their response the more words spawn. So if a new word is created every second then if the user takes 3 seconds to enter their response, 3 words would be created after the user presses enter. Also every word on the board would move down 3 spaces.
- The rate at which words appear should gradually increase as the game goes on.

### Development Tips:
- You will need to read in all the words in the given text file (on Canvas), start with that and verify it works properly.
- Then create three functions:
  - Add a given word at a random x value to the top of the board.
    - Called a number of times when the user presses enter based on the time since they last pressed enter.
  - Move every word down one row on the board.
    - Called a number of times when the user presses enter based on the time since they last pressed enter.
  - Delete a given word from the board
    - Called when a user types the word in.
- Initially just try to get it to run so that it adds a word and moves every other word down when you press enter.
- Then make it so you can type in a word to delete that word.
- Lastly create some kind of timer to create more words the longer the user waits to type. 
  - In previous labs we have done similar things.
- This is not something that will be made easier with ncurses.

******

### Rubric:
- (20pts) Ability for the user to add words to the text file being used.
- (30pts) Randomly choose and place the correct number of  words each time the user types in a response. 
- (15pts) Correctly move all words down the appropriate number of lines each time the user enters a response.
- (30pts) Correctly deleting the intended word after the user types it.
- (5pts) Comments in your code
- (100pts) Total Possible
