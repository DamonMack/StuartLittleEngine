#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>

#include "../IGraphicsEngineRenderer.hpp"
#include "Component.hpp"
#include "../TinyMath.hpp"
#include "TransformComponent.hpp"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class SpriteComponent : public Component{
public:

    /**
     * Constructor
     */
    SpriteComponent(SDL_Renderer* ren, TransformComponent* tc, std::string filePath, bool collide);

    /**
     * Constructor without renderer
     */
    SpriteComponent(TransformComponent* tc, std::string filePath, bool collide);

    /**
     * Constructor from sprite file
    */
    SpriteComponent(std::string filePath, TransformComponent* tc, bool collide);

    /**
     * Constructor from sprite file
    */
    /**
     * Constructor
     */
    ~SpriteComponent();
    
    /**
     * Update the sprites position and frame
     */
    void Update(double dt) override;
    /**
     * Render the sprite 
     */
    void Render(SDL_Renderer *ren) override;

    void SetFlipped(bool flipped);
    /**
     * Gets the colliderID from the sprite
     */
    int GetColliderID();
    /**
     * Creates an SDLRect
     */
    SDL_Rect GetDestRect();
    /**
     * Checks if the sprite is able to collide
     */
    bool doesCollide();

private:
    /**
     * Loads sprite data from a sprite file
    */
    void LoadSprite(std::string filepath);

    Vec2D mPosition;

	unsigned int mCurrentFrame{0};
	unsigned int mLastFrame{7};

    double timeUntilNextFrame=100;
    double timeSinceUpdate=0;

    bool hasCollider;
    bool flipped = false;
    
    // An SDL Surface contains pixel data to draw an image
    std::string mFilePath;
	SDL_Surface* mSpriteSheet =  nullptr;
	SDL_Texture* mTexture =  nullptr;

	SDL_Rect mSrc;
	SDL_Rect mDest;
    float unzoomedScaleX;
    float unzoomedScaleY;

    TransformComponent* transform;
    SDL_Renderer* renderer;

    std::vector<SDL_Rect> m_srcFrames;
    int m_frameCount;

    int colliderID;
};

#endif
