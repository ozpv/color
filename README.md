# color
Convert to and from RGB, HSL, HSV, CMY, CMYK, and HEX in C++

## How to Use:

Create a Color object:

```
Color::HSL hsl;
```

Or with initial values:

```
Color::HSL hsl(34.0, 0.3, 0.5);
```

With the exception of HEX,
You can convert between colorspaces easily.
Just use the assignment operator:

```
Color::HSV hsv;

hsv = hsl;
```

Output the values easily like so:

```
std::cout << hsl << std::endl;    
std::cout << hsv << std::endl;
```

## Why private the variables and friend each class?
Using getters and setters will ensure that HEX has a 24-bit integer MAX, and that HSL and HSV are bound to [0.0, 360.0], [0.0, 1.0], and [0.0, 1.0]. 
You can implement them inside of the classes.
In WIN32, there is an RGB to RGBQUAD getter by default.
