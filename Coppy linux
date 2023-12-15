void isGameOver() {
    // Check if the board is full
    bool boardFull = true;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (arr[i][j] == 0) {
                boardFull = false;
                break;
            }
        }
        if (!boardFull) {
            break;
        }
    }

    // Check for adjacent values in rows or columns
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6 - 1; ++j) {
            if (arr[i][j] == arr[i][j + 1] || arr[j][i] == arr[j + 1][i]) {
                return; // Game is not over
            }
        }
    }

    // If the board is full and no adjacent values found, display GAME OVER button
    if (boardFull) {
        // Display GAME OVER button (you can modify this part based on your UI implementation)
        Button gameOverButton("GAME OVER", Vector2f(200, 50), 20, Color::Red, Color::White);
        gameOverButton.setPosition(Vector2f(400, 300));
        gameOverButton.setFont(font); // Assuming you have the font variable declared globally

        // Draw GAME OVER button over the existing contents
        gameOverButton.drawTo(window);

        window.display();
    }
}
