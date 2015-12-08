//
//  DumbbellMenuItemImage.cpp
//  Dumbbell
//
//  Created by NakadaTakuya on 2015/12/09.
//
//

#include "DumbbellMenuItemImage.hpp"

DumbellMenuItemImage* DumbellMenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback)
{
    return DumbellMenuItemImage::create(normalImage, selectedImage, "", callback);
}

DumbellMenuItemImage* DumbellMenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
    DumbellMenuItemImage *ret = new (std::nothrow) DumbellMenuItemImage();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, callback))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void DumbellMenuItemImage::selected()
{
    MenuItemImage::selected();
    auto scale = ScaleBy::create(0.1, 1.2);
    runAction(scale);
}

void DumbellMenuItemImage::unselected()
{
    MenuItemImage::unselected();
    auto scale = ScaleBy::create(0.1, 1.0/1.2);
    runAction(scale);
}