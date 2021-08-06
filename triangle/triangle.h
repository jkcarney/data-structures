/*  Name: Joshua Carney
    Course: 362-2
    Description: A triangle header class
                 All sides are floating point numbers
                 the class contains member functions ...""
*/
#ifndef triangle_H
#define triangle_H

class triangle {

    private:
    // memeber variables
        float m_side1;
        float m_side2;
        float m_side3;
    
    public:
        // Default constructor: assign 1 to every side
        triangle() {
            m_side1 = 1;
            m_side2 = 1;
            m_side3 = 1;
        }

        // Constructor with single initial value assigned to every side  ;lllllllllllllllllppppppppp                          
        triangle(float x) {
            m_side1 = x;
            m_side2 = x;
            m_side3 = x;
        }

        triangle(float x, float y, float z) {
            m_side1 = x;
            m_side2 = y;
            m_side3 = z;
        }

        float get_side1() const {
            return m_side1;
        }

        float get_side2() const {
            return m_side2;
        }

        float get_side3() const {
            return m_side3;
        }

        void set_side1(const float& x) { // we dont wanna change x
            m_side1 = x;
        }
        
        void set_side2(const float& x) {
            m_side2 = x;
        }

        void set_side3(const float& x) {
            m_side3 = x;
        }

        float perimeter() const;

        float largest_side() const {
            if(m_side1 > m_side2 && m_side1 > m_side3){
                return m_side1;
            } else if(m_side2 > m_side1 && m_side2 > m_side3){
                return m_side2;
            } else {
                return m_side3;
            }
        }

        bool is_right() {
            return  (m_side1 * m_side1) + (m_side2 * m_side2) == (m_side3 * m_side3) ||
                    (m_side2 * m_side2) + (m_side3 * m_side3) == (m_side1 * m_side1) ||
                    (m_side1 * m_side1) + (m_side3 * m_side3) == (m_side2 * m_side2);
        }
};

#endif