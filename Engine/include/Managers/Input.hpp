//
// Created by Jonathan Lehman on 4/6/23.
//

#ifndef FINALPROJECT_SIMON_JON_DAMON_JASON_INPUT_HPP
#define FINALPROJECT_SIMON_JON_DAMON_JASON_INPUT_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <string>
#include <set>

/*!
 * Singleton class which handles all player input.
 */
class Input {

public:
    /*!
     * Obtain the singleton instance of the class. Creates it if it doesn't exist.
     * @return The instance of this class.
     */
    static Input& GetInstance();
    /*!
     * Update the internal status to account for the latest changes in
     * player input.
     */
    void handleInput();
    /*!
     * Is the key with the given name currently being held?
     * @param keyName The SDL name for the key to check.
     * @return Whether or not the given key is being held.
     */
    bool isPressingKey(std::string keyName);
    /*!
     * Has the player given the input to quit the game?
     * @return Whether the player has given the input to quit the game.
     */
    bool gotQuitInput();

private:
    std::set<std::string> heldKeys;
    bool quitInput = false;
};

#endif //FINALPROJECT_SIMON_JON_DAMON_JASON_INPUT_HPP
