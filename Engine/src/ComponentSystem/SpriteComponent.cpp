#include <tuple>
#include <fstream>
#include "ComponentSystem/SpriteComponent.hpp"
#include "Managers/ResourceManager.hpp"
#include "Managers/ColliderManager.hpp"
#include "Managers/Camera.hpp"

SpriteComponent::SpriteComponent(SDL_Renderer* ren, TransformComponent* tc, std::string filePath, bool collide) : transform(tc), renderer(ren), hasCollider(collide) {
    ResourceManager::GetInstance().LoadResource(filePath, ren);
    mTexture = ResourceManager::GetInstance().GetResource(filePath);

    // store this sprite as collider in collider manager and return its index
    // colliderID is stored so collider doesn't check collision with itself
    colliderID = ColliderManager::GetInstance().StoreCollider(this);

    // TODO: add these values as parameters
    mSrc.y = 0;
    mSrc.w = 75;
    mSrc.h = 87;

    mDest.w = 128;
    mDest.h = 128;

    for(int i = 0; i < 6; i++){
        SDL_Rect newRect;
        newRect.x = i * 75;
        newRect.y = 0;
        newRect.w = 75;
        newRect.h = 87;
        m_srcFrames.push_back(newRect);
    }
    m_frameCount = m_srcFrames.size();

}

SpriteComponent::SpriteComponent(TransformComponent* tc, std::string filePath, bool collide) : transform(tc), mFilePath(filePath), hasCollider(collide) {
    // store this sprite as collider in collider manager and return its index
    // colliderID is stored so collider doesn't check collision with itself
    colliderID = ColliderManager::GetInstance().StoreCollider(this);

    // TODO: add these values as parameters
    mSrc.y = 0;
    mSrc.w = 75;
    mSrc.h = 87;

    mDest.w = 128;
    mDest.h = 128;

    for(int i = 0; i < 6; i++){
        SDL_Rect newRect;
        newRect.x = i * 75;
        newRect.y = 0;
        newRect.w = 75;
        newRect.h = 87;
        m_srcFrames.push_back(newRect);
    }
    m_frameCount = m_srcFrames.size();
}

SpriteComponent::SpriteComponent(std::string filePath, TransformComponent* tc, bool collide) : transform(tc), hasCollider(collide) {
    colliderID = ColliderManager::GetInstance().StoreCollider(this);
    LoadSprite(filePath);
}

SpriteComponent::~SpriteComponent() { }

void SpriteComponent::LoadSprite(std::string filepath){

    // get directory of sprite file
    std::string directory = filepath.substr(0, filepath.find_last_of('/'));
    
    std::ifstream file;
    // open the file to start parsing
    file.open(filepath);
    if(file.is_open()){
        std::string line;

        // Retrieve the sprite sheet and create an SDL surface
        getline(file, line);
        std::string spriteSheetPath = directory + '/' + line;
        mFilePath = spriteSheetPath;

        // Retrieve the frame count
        getline(file, line);
        int frameCount = std::stoi(line);
        m_frameCount = frameCount;

        // Retrieve ms per frame
        getline(file, line);
        timeUntilNextFrame = std::stoi(line);

        // Retrieve frame dimensions
        getline(file, line);
        mSrc.w = std::stoi(line);
        mDest.w = mSrc.w;
    
        
        getline(file, line);
        mSrc.h = std::stoi(line);
        mDest.h = mSrc.h;

        // Retrieve the tile information and populate m_frames
        // if frame count is higher than amount of frame data, set x and y to (0,0)
        m_srcFrames.clear();
        for(int i = 0; i < frameCount; i++){
            SDL_Rect newFrame;
            if(getline(file, line)){
                newFrame.x = std::stoi(line);
            }else{
                newFrame.x = 0;
            }
            if(getline(file, line)){
                newFrame.y = std::stoi(line);
            }else{
                newFrame.y = 0;
            }

            newFrame.w = mSrc.w;
            newFrame.h = mSrc.h;
            m_srcFrames.push_back(newFrame);
        }
        m_frameCount = m_srcFrames.size();
        mCurrentFrame = 0;
    }
}

void SpriteComponent::Update(double dt) {
    // Increment the frame that
    // the sprite is playing
    timeSinceUpdate += dt;
    if (timeSinceUpdate > timeUntilNextFrame) {
        mCurrentFrame++;
        if(mCurrentFrame >= m_frameCount){
            mCurrentFrame = 0;
        }
        timeSinceUpdate = 0;
    }

    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
    //mSrc.x = mCurrentFrame*75;
    // mSrc.y = 0;
    // mSrc.w = 75;
    // mSrc.h = 87;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.	
    // mDest.x = transform->position.x;
    // mDest.y = transform->position.y;
    // mDest.w = 128;
    // mDest.h = 128;
}

void SpriteComponent::Render(SDL_Renderer *ren) {
    if (mTexture == nullptr) {
        ResourceManager::GetInstance().LoadResource(mFilePath, ren);
        mTexture = ResourceManager::GetInstance().GetResource(mFilePath);
    }
    std::pair<int, int> screenPoint = Camera::GetInstance().worldToScreenPoint(
            std::pair<int, int>(transform->position.x, transform->position.y));
    mDest.x = screenPoint.first;
    mDest.y = screenPoint.second;
    mDest.w = mSrc.w * Camera::GetInstance().zoom;
    mDest.h = mSrc.h * Camera::GetInstance().zoom;
    if (!flipped) { SDL_RenderCopy(ren, mTexture, &m_srcFrames.at(mCurrentFrame), &mDest); }
    else { SDL_RenderCopyEx(ren, mTexture, &m_srcFrames.at(mCurrentFrame), &mDest, 0, nullptr, SDL_FLIP_HORIZONTAL); }
    mDest.w /= Camera::GetInstance().zoom;
    mDest.h /= Camera::GetInstance().zoom;
}

int SpriteComponent::GetColliderID() {
    return colliderID;
}

SDL_Rect SpriteComponent::GetDestRect() {
    mDest.x = transform->position.x;
    mDest.y = transform->position.y;
    return mDest;
}

bool SpriteComponent::doesCollide() {
    return hasCollider;
}

void SpriteComponent::SetFlipped(bool flipped) {
    this->flipped = flipped;
}