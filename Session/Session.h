#pragma once 
#include "../Image/Image.h"
#include "../Transformations/Transformations.h"
#include <vector>
#include <memory>
#include <utility>
#include <stack>
#include "../Image/ImageFactory.h"
class Image;
class Session{
private:

int id = -1;
static int nextId;
std::stack<Image*> images;
std::stack<Transformations*> transformations;
std::stack<Image*> history;
bool active = true;
ImageFactory* imageFactory;
void clearImages();
void clearTransformations();
void clearHistory();
public:
    Session();
    ~Session() ;
    Session(ImageFactory* factory);
    void addImage(Image* image);
    void loadImage(const std::string& filename);
    void closeImage();
    std::vector<Image*> getImages() const;
    

    void queueTransformation(Transformations* transformation);
    void applyTransformations();
    void undo();

    void save(const std::string& filename) const;
    void saveFirstFileAs(const std::string& newFileName) const;
    void printSessionInfo(std::ostream& out) const;
    void terminate();

    int getId() const { return id; }
    bool isActive() const { return active; }
    bool hasImages() const { return !images.empty(); }

};