
# Catan Game Project

This repository contains the implementation of a Catan-like game using C++. The project involves various components like plots, roads, houses, players, and development cards, all managed through a central game board.

## Project Structure

### Source Files (`cpp/`)

- **Demo.cpp**
  - **Purpose**: Demonstrates the overall functionality of the game by interacting with various components.
  - **Functions**: Likely contains the `main` function, setting up a game scenario, initializing components, and showcasing gameplay.

- **Houses.cpp**
  - **Purpose**: Implements the `Houses` class.
  - **Functions**: Manages the creation, storage, and properties of houses. Functions might include constructors, setters, and getters for house attributes.

- **Plot.cpp**
  - **Purpose**: Implements the `Plot` class.
  - **Functions**: Manages plots of land on the game board, including their properties and interactions with other components. Functions likely include constructors and methods to manipulate plot data.

- **Road.cpp**
  - **Purpose**: Implements the `Road` class.
  - **Functions**: Manages the creation and properties of roads. Functions likely include constructors and methods to build and manipulate roads.

- **board.cpp**
  - **Purpose**: Implements the `Board` class.
  - **Functions**: Manages the game board, including the placement of plots, roads, and houses. Functions likely include methods to initialize the board, place components, and check game states.

- **catan.cpp**
  - **Purpose**: Contains the core logic of the Catan game.
  - **Functions**: Manages game rules, player interactions, and overall game flow. Functions likely include methods for starting the game, handling player turns, and enforcing game rules. Specific functions include:
    - **placeSettlement**: Allows a player to place a settlement on the board. This function checks if the placement is valid (e.g., not too close to other settlements, the player has enough resources) and updates the game state accordingly.
    - **placeRoad**: Allows a player to place a road on the board. This function checks for valid placement (e.g., adjacent to existing roads or settlements of the player) and updates the game state.
    - **buildCity**: Allows a player to upgrade a settlement to a city. This function checks if the player has an existing settlement at the location and enough resources to upgrade, then updates the game state.
    - **trade**: Manages trading between players or with the bank. This function handles the exchange of resources, ensuring both parties have agreed to the trade and have the necessary resources.

- **deck.cpp**
  - **Purpose**: Implements the `Deck` class.
  - **Functions**: Manages the deck of development cards used in the game. Functions likely include shuffling the deck, drawing cards, and handling card actions.

- **player.cpp**
  - **Purpose**: Implements the `Player` class.
  - **Functions**: Manages player-specific data, such as resources, buildings, and actions. Functions likely include constructors, resource management, and methods to perform player actions.

### Header Files (`hpp/`)

- **DevelopmentCard.hpp**
  - **Purpose**: Declares the `DevelopmentCard` class.
  - **Functions**: Defines the interface for development cards, including properties and actions.

- **Houses.hpp**
  - **Purpose**: Declares the `Houses` class.
  - **Functions**: Defines the interface for house-related functionalities.

- **Plot.hpp**
  - **Purpose**: Declares the `Plot` class.
  - **Functions**: Defines the interface for plot-related functionalities.

- **Road.hpp**
  - **Purpose**: Declares the `Road` class.
  - **Functions**: Defines the interface for road-related functionalities.

- **board.hpp**
  - **Purpose**: Declares the `Board` class.
  - **Functions**: Defines the interface for board-related functionalities.

- **catan.hpp**
  - **Purpose**: Declares the core functionalities and game rules of the Catan game.
  - **Functions**: Defines the interface for managing game logic and player interactions, including methods for placing settlements, placing roads, building cities, and trading resources.

- **deck.hpp**
  - **Purpose**: Declares the `Deck` class.
  - **Functions**: Defines the interface for deck-related functionalities.

- **doctest.h**
  - **Purpose**: Header for the `doctest` unit testing framework.
  - **Functions**: Provides macros and functions for writing and running unit tests.

- **player.hpp**
  - **Purpose**: Declares the `Player` class.
  - **Functions**: Defines the interface for player-related functionalities.

### Test Files (`tests/`)

- **test_catan.cpp**
  - **Purpose**: Contains unit tests for verifying the functionality of the game components.
  - **Functions**: Includes test cases to ensure that the various classes and methods work as expected.

## The Logic Behind the Functions

- **Initialization**: The game starts by initializing the board, creating players, and setting up initial resources and components like plots, roads, and houses.
- **Game Flow**: Managed by the core logic in `catan.cpp`, which handles player turns, resource management, and rule enforcement.
- **Component Management**: Each component (houses, plots, roads, development cards) has its own class to encapsulate its properties and behaviors, promoting modularity and reusability.
- **User Interaction**: The demo file (`Demo.cpp`) showcases how the user interacts with the game, possibly through a command-line interface or a graphical interface if integrated with a library like Qt.
- **Testing**: Ensures that each component functions correctly and integrates seamlessly with other components, providing a reliable game experience.

### Detailed Functions:

- **placeSettlement**
  - **Purpose**: Allows a player to place a settlement on the board.
  - **Logic**: Checks if the placement is valid (e.g., not too close to other settlements, the player has enough resources), then updates the game state to reflect the new settlement.

- **placeRoad**
  - **Purpose**: Allows a player to place a road on the board.
  - **Logic**: Validates placement (e.g., adjacent to existing roads or settlements of the player), then updates the game state to include the new road.

- **buildCity**
  - **Purpose**: Upgrades a player's settlement to a city.
  - **Logic**: Checks if there is an existing settlement at the location and if the player has enough resources to upgrade. If valid, the settlement is upgraded to a city, and the game state is updated.

- **trade**
  - **Purpose**: Manages resource trading between players or with the bank.
  - **Logic**: Ensures both parties have agreed to the trade and have the necessary resources. Updates the resource counts for both parties involved in the trade.

This structured approach allows for clear separation of concerns, making the codebase easier to manage, extend, and debug.

## Building the Project

To build the project, run the following command in the terminal:

```sh
make
```

To clean the build files, run:

```sh
make clean
```

## Running the Demo

After building the project, run the demo executable to see the game in action using the command:

```sh
make catan
```

## Running the Test

To run the test executable, use the command:

```sh
make test
```

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contact

For any questions or issues, please open an issue on the repository.

---

GitHub Repository: [asafShemesh/matala3-marachot-4](https://github.com/asafShemesh/matala3-marachot-4)
