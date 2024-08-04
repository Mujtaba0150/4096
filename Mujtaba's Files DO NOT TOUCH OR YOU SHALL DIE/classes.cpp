#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button {
    public:
    Button(string t, Vector2f size, int charSize, Color bgColor, Color textColor, float padding = 5.0f)
        : padding(padding), charSize(charSize) {
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);
        button.setSize(size);
        button.setFillColor(bgColor);
        centerText();
    }

    void setFont(Font& font) {
        text.setFont(font);
    }

    void setBackColor(Color color) {
        button.setFillColor(color);
    }

    void setTextColor(Color color) {
        text.setFillColor(color);
    }

    void setText(string t) {
        text.setString(t);
        adjustTextSize();
        centerText();
    }

    void setPosition(Vector2f pos) {
        button.setPosition(pos);
        adjustTextSize();
        centerText();
    }

    void setPadding(float newPadding) {
        padding = newPadding;
        adjustTextSize();
        centerText();
    }

    Vector2f getPosition() const {
        return button.getPosition();
    }

    Vector2f getSize() const {
        return button.getSize();
    }

    void drawTo(RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }

    bool coursorInbound(RenderWindow& window) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        return button.getGlobalBounds().contains(mousePos);
    }

    void leftalign(Vector2f pos, float textOffset) {
        button.setPosition(pos);
        float xPos = pos.x + textOffset;
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);
    }

    Text getText() {
        return text;
    }

    private:
    RectangleShape button;
    Text text;
    float padding;
    int charSize;

    void centerText() {
        FloatRect textBounds = text.getLocalBounds();
        FloatRect buttonBounds = button.getLocalBounds();
        float xPos = button.getPosition().x + (buttonBounds.width - textBounds.width) / 2 - textBounds.left;
        float yPos = button.getPosition().y + (buttonBounds.height - textBounds.height) / 2 - textBounds.top;
        text.setPosition(xPos, yPos);
    }

    void adjustTextSize() {
        FloatRect buttonBounds = button.getLocalBounds();
        float maxWidth = buttonBounds.width - 2 * padding;
        float maxHeight = buttonBounds.height - 2 * padding;

        text.setCharacterSize(charSize);
        FloatRect textBounds = text.getLocalBounds();

        if (textBounds.width > maxWidth || textBounds.height > maxHeight) {
            float widthScale = maxWidth / textBounds.width;
            float heightScale = maxHeight / textBounds.height;

            float scale = std::min(widthScale, heightScale);

            text.setCharacterSize(static_cast<int>(charSize * scale));
        }
    }
};

class Picture {
    public:
    Picture(string filePath) {
        texture.loadFromFile(filePath);
        sprite.setTexture(texture);
    }
    void SetTexture(string filePath) {
        texture.loadFromFile(filePath);
        sprite.setTexture(texture);
    }
    void setScale(sf::Vector2f scale) {
        scale.x = std::max(scale.x, 0.1f); // Minimum scale to avoid division by zero
        scale.y = std::max(scale.y, 0.1f);

        // Calculate aspect ratio
        sf::Vector2f Aspectratio(scale.x / texture.getSize().x, scale.y / texture.getSize().y);

        // Set scale of sprite
        sprite.setScale(Aspectratio);
    }
    void setPosition(sf::Vector2f position) {
        sprite.setPosition(position);
    }
    void drawTo(sf::RenderWindow& window) {
        window.draw(sprite);
    }
    Vector2f getPosition() {
        return sprite.getPosition();
    }
    Vector2f getSize() {
        return sprite.getScale();
    }
    Vector2f getsizeText() {
        return Vector2f(texture.getSize().x, texture.getSize().y);
    }
    void move(double x, double y) {
        sprite.move(x, y);
    }
    FloatRect getGlobalBounds() {
        return sprite.getGlobalBounds();
    }
    void rotate(float angle) {
        sprite.rotate(angle);
    }

    private:
    sf::Texture texture;
    sf::Sprite sprite;
};