#include <cstdint>
#include <iostream>

namespace Color {
    class RGB;
    class HSL;
    class HSV;
    class HEX;
    RGB HSL_To_RGB(HSL& hsl);
    RGB HSV_To_RGB(HSV& hsv);
    HSL RGB_To_HSL(RGB& rgb);
    HSL HSV_To_HSL(HSV& hsv);
    HSV RGB_To_HSV(RGB& rgb);
    HSV HSL_To_HSV(HSL& hsl);
    HEX RGB_To_HEX(RGB& rgb);
    HEX HSL_To_HEX(HSL& hsl);

    class RGB {
        public:
            RGB() : Red(0), Green(0), Blue(0) {}
            RGB(uint8_t red, uint8_t green, uint8_t blue) : Red(red & 0xFF), Green(green & 0xFF), Blue(blue & 0xFF) {}
            ~RGB() {}

            void operator=(HSL& hsl) {
                RGB rgb(HSL_To_RGB(hsl));
                this->Red = rgb.Red;
                this->Green = rgb.Green;
                this->Blue = rgb.Blue;
            }

            void operator=(HSV& hsv) {
                RGB rgb(HSV_To_RGB(hsv));
                this->Red = rgb.Red;
                this->Green = rgb.Green;
                this->Blue = rgb.Blue;
            }
            
        #ifdef _WIN32
            RGBQUAD RGB_To_RGBQUAD() {
                return { this->Red, this->Green, this->Blue, this->Reserved }; 
            }
        #endif

            friend std::ostream& operator<<(std::ostream& out, const RGB& rgb) {
                out << static_cast<int>(rgb.Red) << " " << static_cast<int>(rgb.Green) << " " << static_cast<int>(rgb.Blue);
                return out;
            } 

            friend RGB HSL_To_RGB(HSL& hsl);
            friend RGB HSV_To_RGB(HSV& hsv);
            friend HSL RGB_To_HSL(RGB& rgb);
            friend HSV RGB_To_HSV(RGB& rgb);
            friend HEX RGB_To_HEX(RGB& rgb);
        private:
            uint8_t Red;
            uint8_t Green;
            uint8_t Blue;
        #ifdef _WIN32
            const uint8_t Reserved = 0;
        #endif
    };

    class HSL {
        public:
            HSL() : Hue(0), Saturation(0), Lightness(0) {}
            HSL(double hue, double saturation, double lightness) : Hue(hue > 360 ? 360 : hue), Saturation(saturation > 1 ? 1 : saturation), Lightness(lightness > 1 ? 1 : lightness) {}
            ~HSL() {}

            void operator=(RGB& rgb) {
                HSL hsl(RGB_To_HSL(rgb));
                this->Hue = hsl.Hue;
                this->Saturation = hsl.Saturation;
                this->Lightness = hsl.Lightness;
            }

            void operator=(HSV& hsv) {
                HSL hsl(HSV_To_HSL(hsv));
                this->Hue = hsl.Hue;
                this->Saturation = hsl.Saturation;
                this->Lightness = hsl.Lightness;
            }

            friend std::ostream& operator<<(std::ostream& out, const HSL& hsl) {
                out << hsl.Hue << " " << hsl.Saturation << " " << hsl.Lightness;
                return out;
            }

            friend HSL RGB_To_HSL(RGB& rgb);
            friend HSL HSV_To_HSL(HSV& hsv);
            friend HSV HSL_To_HSV(HSL& hsl);
            friend RGB HSL_To_RGB(HSL& hsl);
        private:
            double Hue;
            double Saturation;
            double Lightness;
    };

    class HSV {
        public:
            HSV() : Hue(0), Saturation(0), Value(0) {}
            HSV(double hue, double saturation, double value) : Hue(hue), Saturation(saturation), Value(value) {}
            ~HSV() {}

            void operator=(RGB& rgb) {
                HSV hsv(RGB_To_HSV(rgb));
                this->Hue = hsv.Hue;
                this->Saturation = hsv.Saturation;
                this->Value = hsv.Value;
            }

            void operator=(HSL& hsl) {
                HSV hsv(HSL_To_HSV(hsl));
                this->Hue = hsv.Hue;
                this->Saturation = hsv.Saturation;
                this->Value = hsv.Value;
            }

            friend std::ostream& operator<<(std::ostream& out, const HSV& hsv) {
                out << hsv.Hue << " " << hsv.Saturation << " " << hsv.Value;
                return out;
            }

            friend RGB HSV_To_RGB(HSV& hsv);
            friend HSL HSV_To_HSL(HSV& hsv);
            friend HSV RGB_To_HSV(RGB& rgb);
            friend HSV HSL_To_HSV(HSL& hsl);
        private:
            double Hue;
            double Saturation;
            double Value;
    };

    class HEX {
        public:
            HEX() : Hex(0x000000) {}
            HEX(uint32_t hex) : Hex(hex & 0xFFFFFF) {}
            ~HEX() {}

            void operator=(RGB& rgb) {
                HEX hex(RGB_To_HEX(rgb));
                this->Hex = hex.Hex;
            }

            void operator=(HSL& hsl) {
                HEX hex(HSL_To_HEX(hsl));
                this->Hex = hex.Hex;
            }
            
            friend std::ostream& operator<<(std::ostream& out, const HEX& hex) {
                out << "0x" << std::hex << std::uppercase << hex.Hex << std::dec;
                return out;
            }

            friend HEX RGB_To_HEX(RGB& rgb);
            friend HEX HSL_To_HEX(HSL& hsl);
        private:
            uint32_t Hex;
    };

    template<typename Type>
    inline Type tmax(Type a, Type b) {
	    return (a > b) ? a : b;
    }

    template<typename Type>
    inline Type tmin(Type a, Type b) {
    	return (a < b) ? a : b;
    }

    template<typename Type>
    inline Type tmax3(Type a, Type b, Type c) {
    	return tmax<Type>(tmax<Type>(a, b), c);
    }

    template<typename Type>
    inline Type tmin3(Type a, Type b, Type c) {
    	return tmin<Type>(tmin<Type>(a, b), c);
    }

    template<typename Type>
    inline Type tmod(Type value, Type mod) {
		if (value >= mod) {
			value -= mod;
			/* recursion to ensure the MOD value */
			tmod(value, mod);
		}
		return value;
	}

    inline double Hue_To_Color(double p, double q, double t) {
		if (t < 0.0)
			t++;
		if (t > 1.0)
			t--;
		if (1.0 / 6.0 > t)
			return p + (q - p) * 6.0 * t;
		if (1.0 / 2.0 > t)
			return q;
		if (2.0 / 3.0 > t)
			return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
		return p;
	}

    inline double Hue_From_Color(double red, double green, double blue, double max, double chroma) {
        double hue;

        if (max == red)
			hue = (green - blue) / chroma + (green < blue ? 6.0 : 0.0);
		else if (max == green)
			hue = (blue - red) / chroma + 2.0;
		else if (max == blue)
			hue = (red - green) / chroma + 4.0;
        
        return hue;
    }

    RGB HSL_To_RGB(HSL& hsl) {
        RGB rgb;

		double k;

		double a = hsl.Saturation * tmin<double>(hsl.Lightness, 1 - hsl.Lightness);

		/* to catch our RGB values */
		double rgbd[3];

		/* to calculate f(0) f(8) f(4) */
		double n[3] = { 0.0, 8.0, 4.0 };

		for (int i = 0; i < 3; i++) {
			k = (n[i] + hsl.Hue / 30.0);

			/* simple mod template */
			k = tmod<double>(k, 12);

			rgbd[i] = hsl.Lightness - a * tmax<double>(-1.0, tmin3<double>(k - 3.0, 9.0 - k, 1.0));
		}

		rgb.Red = static_cast<uint8_t>(rgbd[0] * 255.0);
		rgb.Green = static_cast<uint8_t>(rgbd[1] * 255.0);
		rgb.Blue = static_cast<uint8_t>(rgbd[2] * 255.0);

        return rgb;
    }

    RGB HSV_To_RGB(HSV& hsv) {
        RGB rgb;

		double k;

		/* to catch our RGB values */
		double rgbd[3];

		/* to calculate f(5) f(3) f(1) */
		double n[3] = { 5.0, 3.0, 1.0 };

		for (int i = 0; i < 3; i++) {
			k = (n[i] + hsv.Hue / 60.0);

			/* simple mod template */
			k = tmod<double>(k, 6);

			rgbd[i] = hsv.Value - (hsv.Value * hsv.Saturation * tmax<double>(0, tmin3<double>(k, 4 - k, 1)));
		}

		rgb.Red = static_cast<uint8_t>(rgbd[0] * 255.0);
		rgb.Green = static_cast<uint8_t>(rgbd[1] * 255.0);
		rgb.Blue = static_cast<uint8_t>(rgbd[2] * 255.0);

        return rgb;
    }

    HSL RGB_To_HSL(RGB& rgb) {
        HSL hsl;

        /* scale our values to between [0, 1]
		 * cast our vaules to T to ensure the compiler interprets it correctly
		 */
		double red = static_cast<double>(rgb.Red) / 255.0;
		double green = static_cast<double>(rgb.Green) / 255.0;
		double blue = static_cast<double>(rgb.Blue) / 255.0;

		double max = tmax3<double>(red, green, blue);
		double min = tmin3<double>(red, green, blue);

		/* calculate chroma */
		double chroma = max - min;

		double hue;
		double saturation;

		/* calculate the lightness value by averaging max and min */
		double lightness = (max + min) / 2.0;

		/* color is achromatic and we don't need to calculate the hue */
		if (max == min) {
			hue = 0.0;
			saturation = 0.0;
		} else {
			/* calculate saturation */
			saturation = (lightness > 0.5) ? chroma / (2.0 - max - min) : chroma / (max + min);

			/* calculate color */
            hue = Hue_From_Color(red, green, blue, max, chroma);
		}

		/* scale the hue from distance to distance in degrees by multiplying by 60 */
        hsl.Hue = hue * 60.0;
		hsl.Saturation = saturation;
		hsl.Lightness = lightness;

        return hsl;
    }

    HSL HSV_To_HSL(HSV& hsv) {
        HSL hsl;

        hsl.Hue = hsv.Hue;
        hsl.Lightness = hsv.Value * (1.0 - (hsv.Saturation / 2.0));

        if (hsl.Lightness == 0.0 || hsl.Lightness == 1.0) {
            hsl.Saturation = 0.0;
        } else {
            hsl.Saturation = (hsv.Value - hsl.Lightness) / tmin<double>(hsl.Lightness, 1 - hsl.Lightness);
        }

        return hsl;
    }

    HSV RGB_To_HSV(RGB& rgb) {
        HSV hsv;

        /* scale our values to between [0, 1]
		 * cast our vaules to T to ensure the compiler interprets it correctly
		 */
		double red = static_cast<double>(rgb.Red) / 255.0;
		double green = static_cast<double>(rgb.Green) / 255.0;
		double blue = static_cast<double>(rgb.Blue) / 255.0;

		double max = tmax3<double>(red, green, blue);
		double min = tmin3<double>(red, green, blue);

		/* calculate chroma */
		double chroma = max - min;

        double hue;
		double saturation;

        double value = max;

        if (max == min) {
            hue = 0.0;
            saturation = 0.0;
        } else {
            /* calculate saturation */
			saturation = (max > 0.0) ? chroma / max : 0.0;

            /* calculate color */
            hue = Hue_From_Color(red, green, blue, max, chroma);
        }

        /* scale the hue from distance to distance in degrees by multiplying by 60 */
        hsv.Hue = hue * 60.0;
		hsv.Saturation = saturation;
		hsv.Value = value;

        return hsv;
    }

    HSV HSL_To_HSV(HSL& hsl) {
        HSV hsv;

        hsv.Hue = hsl.Hue;
        hsv.Value = hsl.Lightness + (hsl.Saturation * tmin<double>(hsl.Lightness, 1.0 - hsl.Lightness));
        hsv.Saturation = hsv.Value == 0.0 ? 0.0 : 2.0 * (1.0 - (hsl.Lightness / hsv.Value));

        return hsv;
    }

    HEX RGB_To_HEX(RGB& rgb) {
        HEX hex;
        hex.Hex = ((rgb.Red) << 16) + ((rgb.Green) << 8) + (rgb.Blue);
        return hex;
    }

    HEX HSL_To_HEX(HSL& hsl) {
        HEX hex;
        RGB rgb;
        rgb = hsl;
        hex = RGB_To_HEX(rgb);
        return hex.Hex;
    }
}

using namespace Color;

int main(void) {
    HSL hsl(34.0, 0.3, 0.5);
    HSV hsv;

    hsv = hsl;

    std::cout << hsl << std::endl;
    
    std::cout << hsv << std::endl;

    hsl = hsv;

    std::cout << hsl << std::endl;

    return 0;
}