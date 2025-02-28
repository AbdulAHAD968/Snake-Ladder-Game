#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<cmath>


using namespace std;


const int N = 100;
const int boardSize = 10;
const int cellSize = 51;


// DISPLAY THE WINNER PROFILE.
void WIN_SCREEN(const string& winner){

    sf::RenderWindow winWindow(sf::VideoMode(720, 400), "WINNER SCREEN");

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("1.png")){
        throw runtime_error("FAILED TO LOAD BACKGROUND IMAGE!");
    }

    // Create a sprite for the background
    sf::Sprite background(bgTexture);
    background.setScale(
        winWindow.getSize().x / static_cast<float>(bgTexture.getSize().x),
        winWindow.getSize().y / static_cast<float>(bgTexture.getSize().y)
    );

    // Load a font for the text
    sf::Font font;
    if (!font.loadFromFile("/home/kali/Desktop/luddo/pacifico/Pacifico.ttf")) {
        throw runtime_error("ERROR: Could not load font file!");
    }

    // Create the winner text
    sf::Text winText;
    winText.setFont(font);
    winText.setString(winner + " WINS!!!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::Yellow);
    winText.setStyle(sf::Text::Bold);
    winText.setOutlineColor(sf::Color::Black);
    winText.setOutlineThickness(3);

    // Center the text
    sf::FloatRect textBounds = winText.getLocalBounds();
    winText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    winText.setPosition(winWindow.getSize().x / 2, winWindow.getSize().y / 2);

    // Display the winner screen
    while (winWindow.isOpen()) {
        sf::Event event;
        while (winWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                winWindow.close();
                return;
            }
        }

        winWindow.clear();
        winWindow.draw(background);
        winWindow.draw(winText);
        winWindow.display();
    }
}



int moves[N];

// Function to initialize the board
void INITIALIZE_ME() {
    for (int i = 0; i < N; i++)
        moves[i] = -1;

    // Ladders
    moves[2] = 38;
    moves[4] = 14;
    moves[9] = 31;
    moves[21] = 42;
    moves[28] = 84;
    moves[51] = 67;
    moves[72] = 91;

    // Snakes
    moves[98] = 79;
    moves[95] = 75;
    moves[93] = 73;
    moves[87] = 24;
    moves[64] = 60;
    moves[62] = 19;
    moves[17] = 7;
}

//FUNCTION TO CALCULATE THE PLAYER POSITION ON
sf::Vector2f getPosition(int cell) {
    int row = cell / boardSize;
    int col = cell % boardSize;

    if (row % 2 == 1) col = boardSize - col - 1;

    return sf::Vector2f(col * cellSize, (boardSize - row - 1) * cellSize);
}

//FUNCTION TO SIMULATE THE DICE ROLLING.
int ROLL_DICE(){
    return rand() % 6 + 1;
}

// FUNCTION TO GENERATE RANDOM COLORS.
sf::Color randomColor(){
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}


// Function to draw snakes and ladders with arrowheads
void LADDER_AND_SNAKES(sf::RenderWindow &window, const int moves[N]) {
    for (int i = 0; i < N; ++i){
        if (moves[i] != -1){
            sf::Vector2f start = getPosition(i) + sf::Vector2f(cellSize / 2, cellSize / 2);
            sf::Vector2f end = getPosition(moves[i]) + sf::Vector2f(cellSize / 2, cellSize / 2);

            sf::Vector2f direction = end - start;
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;

            // Adjust end position for arrowhead placement
            sf::Vector2f adjustedEnd = end - direction * 15.f; // Move back by arrowhead size

            // Draw the main line
            sf::RectangleShape line(sf::Vector2f(length - 12.f, 5)); // Reduced length for arrowhead space
            line.setPosition(start);
            line.setRotation(atan2(direction.y, direction.x) * 180.f / 3.14159f);
            line.setFillColor((i < moves[i]) ? sf::Color::Green : sf::Color::Red); // Ladder: Green, Snake: Red

            window.draw(line);

            // Draw the arrowhead
            sf::CircleShape arrowHead(10, 3); // Triangle with radius 10
            arrowHead.setFillColor((i < moves[i]) ? sf::Color::Green : sf::Color::Red);

            arrowHead.setOrigin(10, 10); // Center the arrowhead
            arrowHead.setPosition(adjustedEnd);
            arrowHead.setRotation(atan2(direction.y, direction.x) * 180.f / 3.14159f + 90.f); // Rotate to match direction

            window.draw(arrowHead);
        }
    }
}



//* MAIN FUNCTION. *//
int main(){

    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(boardSize * cellSize, boardSize * cellSize + 80), "SNAKE AND LADDER");
    
    INITIALIZE_ME();

    sf::Font font;
    if(!font.loadFromFile("/home/kali/Desktop/luddo/Lobster/Lobster_1.3.otf")){
        cout<<"\n ERROR LOADING FONT FILE.  [GOTHAM WALA FONT]"<<endl;
        return -1;
    }

    vector<sf::RectangleShape> cells(N);
    vector<sf::Text> cellNumbers(N);
    
    for(int i=0 ; i<N ; i++){

        cells[i].setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
        cells[i].setPosition(getPosition(i));
        cells[i].setFillColor(randomColor());
        cells[i].setOutlineThickness(2);
        cells[i].setOutlineColor(sf::Color::Black);

        cellNumbers[i].setFont(font);
        cellNumbers[i].setString(to_string(i + 1));
        cellNumbers[i].setCharacterSize(12);
        cellNumbers[i].setFillColor(sf::Color::White);
        sf::FloatRect textBounds = cellNumbers[i].getLocalBounds();
        cellNumbers[i].setPosition(
            cells[i].getPosition().x + (cellSize - textBounds.width) / 2 - 5,
            cells[i].getPosition().y + (cellSize - textBounds.height) / 2 - 5
        );
    }

    int rot = cellSize / 6;

    // Player 1 Goti
    sf::CircleShape GOTI_1(rot, 30); // 30 points for smooth circle
    GOTI_1.setFillColor(sf::Color::Red);
    GOTI_1.setOutlineThickness(5); // 5-pixel wide outline
    GOTI_1.setOutlineColor(sf::Color(250, 150, 100)); // Orange outline
    GOTI_1.setPosition(getPosition(0));

    // Player 2 Goti
    sf::CircleShape GOTI_2(rot, 30); // 30 points for smooth circle
    GOTI_2.setFillColor(sf::Color::Magenta);
    GOTI_2.setOutlineThickness(5); // 5-pixel wide outline
    GOTI_2.setOutlineColor(sf::Color::Green); // Orange outline
    GOTI_2.setPosition(getPosition(0));

    int player1Pos = 0, player2Pos = 0;
    bool player1Turn = true;

    sf::Text diceText;
    diceText.setFont(font);
    diceText.setCharacterSize(24);
    diceText.setFillColor(sf::Color::White);
    diceText.setPosition(40, boardSize * cellSize + 20);

    sf::Text player1Text;
    player1Text.setFont(font);
    player1Text.setCharacterSize(20);
    player1Text.setFillColor(sf::Color::Red);
    player1Text.setPosition(10, boardSize * cellSize + 50);

    sf::Text player2Text;
    player2Text.setFont(font);
    player2Text.setCharacterSize(20);
    player2Text.setFillColor(sf::Color::Magenta);
    player2Text.setPosition(boardSize * cellSize - 160, boardSize * cellSize + 50);

    sf::RectangleShape rollButton(sf::Vector2f(100, 30));
    rollButton.setFillColor(sf::Color::Blue);
    rollButton.setPosition((boardSize * cellSize - 100) / 2 + 140, boardSize * cellSize + 15);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("ROLL DICE");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(
        rollButton.getPosition().x + 10,
        rollButton.getPosition().y + 5
    );

    bool gameWon = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameWon && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left){

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (rollButton.getGlobalBounds().contains(mousePos.x, mousePos.y)){

                    int dice = ROLL_DICE();
                    diceText.setString("DICE :: " + to_string(dice)); // Dice ka result hamesha display karein

                    int &currentPlayerPos = player1Turn ? player1Pos : player2Pos;
                    sf::CircleShape &currentToken = player1Turn ? GOTI_1 : GOTI_2;

                    int nextPos = currentPlayerPos + dice;

                    // Agar next position board se bahar chali jaye
                    if (nextPos >= N) {
                        // Skip current player's turn
                        diceText.setString("DICE :: [" + to_string(dice) + "] (Move skipped!)");
                    }
                    else if (nextPos == N - 1) { // Agar player exactly last position par pauchta hai
                        gameWon = true;
                        currentPlayerPos = N - 1; // Final position par le jayein
                        currentToken.setPosition(getPosition(currentPlayerPos));
                        string winner = player1Turn ? "PLAYER [1]" : "PLAYER [2]";
                        WIN_SCREEN(winner);
                        break;
                    }
                    else {
                        // Check karein agar snake ya ladder ho
                        if (moves[nextPos] != -1) {
                            nextPos = moves[nextPos];
                        }
                        currentPlayerPos = nextPos;
                        currentToken.setPosition(getPosition(currentPlayerPos));
                    }

                    player1Turn = !player1Turn; // Next player's turn
                }


            }
        }

        player1Text.setString("PLAYER [1] :: " + to_string(player1Pos + 1));
        player2Text.setString("PLAYER [2] :: " + to_string(player2Pos + 1));

        window.clear();

        for(int i=0 ; i<N ; i++){
            window.draw(cells[i]);
            window.draw(cellNumbers[i]);
        }

        LADDER_AND_SNAKES(window, moves);

        window.draw(GOTI_1);
        window.draw(GOTI_2);

        window.draw(rollButton);
        window.draw(buttonText);

        window.draw(diceText);
        window.draw(player1Text);
        window.draw(player2Text);

        window.display();
    }

    return 0;
}
