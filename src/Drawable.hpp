
#pragma once

/// @brief @interface for a drawable object
struct Drawable {
    virtual ~Drawable() {}
    
    /// @brief Override me!
    virtual void draw () const = 0;
};
