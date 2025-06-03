#pragma once 
#include "../Image/Image.h"
#include "../Transformations/Transformations.h"
#include <vector>
#include <memory>
#include <utility>
#include <stack>
#include "../Image/ImageFactory.h"
#include "../System/System.h"
class Image;
class Session{
private:
int id ;
static int nextId;
std::vector<Image*> images;
std::vector<Transformations*> pendingTransformations;
std::vector<std::vector<Image*>> history;
std::vector<std::vector<Transformations*>> transformationsHistory;
bool active = true;
ImageFactory* imageFactory;
std::vector<Image*> cloneImages(const std::vector<Image*>& source);
void clearImages();
void clearTransformations();
void clearHistory();
public:
    Session();
    ~Session() ;
    void saveState();
    void addImage(Image* image);
    void loadImage(const std::string& filename);
    void closeImage();
    std::vector<Image*> getImages() const;
    
    std::vector<Transformations*> cloneTransformations(
    const std::vector<Transformations*>& source);

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    void queueTransformation(Transformations* transformation);
    void applyTransformations(System& system);
    bool hasPendingTransformations() const;
    void undo();

    void save(const std::string& filename) const;
    void saveFirstFileAs(const std::string& newFileName) const;
    void printSessionInfo(std::ostream& out) const;
    void terminate();

    static void resetSessionCounter();
    int getId() const { return id; }
    bool isActive() const { return active; }
    bool hasImages() const { return !images.empty(); }

};