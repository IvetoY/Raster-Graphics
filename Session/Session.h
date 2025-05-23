#pragma once 
#include "../Image/Image.h"
#include "../Transformations/Transformations.h"
#include <vector>
#include <memory>
#include <utility>
#include <stack>
class Session{
private:
int id;
std::vector<Image*> images;
std::vector<Transformations*> pendingTransformations;
std::stack<Image*> history;
bool active = true;
public:
    explicit Session(int _id);
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    ~Session() = default;
    void addImage(Image* image);
    void addTransformation(Transformations* transform);
    void applyTransformations();

    void loadImage(const String& filename);
    void saveImage(const String& filename);
    void closeImage();
    void terminate();
    bool isActive() const;

    void undo();

    int getId() const;
    const std::vector<Image*>& getImages() const;
    const std::vector<Transformations*>& getPendingTransformations() const;
};