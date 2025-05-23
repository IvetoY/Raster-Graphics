#include "Save.h"
#include "../Session/Session.h"
#include "../Image/Image.h"

Save::Save(const String& _path, size_t _id) : filePath(_path), imageId(_id) {}
void Save::apply(Session& session) {
    std::vector<Image*> images = session.getImages();
    if(images.empty()) {throw std::runtime_error("No images to save in the session!");}
    if(imageId == -1){
        for (const auto& img : images){
            if(img){
                img->save(filePath);
            }
        }
    }
    else{
        if (imageId < 0 || imageId >= static_cast<int>(images.size())){
            throw std::out_of_range("Invalid image index!");
        }
        if(images[imageId]){images[imageId]->save(filePath);}
    }
}
