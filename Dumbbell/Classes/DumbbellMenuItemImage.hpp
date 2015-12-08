//
//  DumbbellMenuItemImage.hpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/09.
//
//

#ifndef DumbbellMenuItemImage_hpp
#define DumbbellMenuItemImage_hpp
USING_NS_CC;

class DumbellMenuItemImage : public MenuItemImage
{
public:
    static DumbellMenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);
    static DumbellMenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const std::string&disabledImage, const ccMenuCallback& callback);
    virtual void selected();
    virtual void unselected();
};

#endif /* DumbbellMenuItemImage_hpp */
