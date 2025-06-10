#include <iostream>
#include <cmath>
#include <concepts>

template<typename T>
    requires std::integral<T> || std::floating_point<T>
class Polynomial{
    private:
    int degree; //차수
    T* coeffs; //계수 배열

    public:
    //매개변수 있는 생성자
    Polynomial(int deg, const T* c) : degree(deg){
        coeffs = new T[deg + 1];
        for (int i = 0; i <= deg; i++){
            coeffs[i] = c[i];
        }
    }
    //소멸자
    ~Polynomial(){ delete[] coeffs; }
    //복사 생성자
    Polynomial(const Polynomial& other) : degree(other.degree){
        coeffs = new T[other.degree + 1];
        for (int i = 0; i <= other.degree; i++){
            coeffs[i] = other.coeffs[i];
        }
    }
    //이동 생성자
    Polynomial(Polynomial&& other) noexcept
        : degree(other.degree), coeffs(other.coeffs) {
        degree = -1;
        coeffs = nullptr;
    }
    //복사 대입 연산자
    Polynomial& operator=(const Polynomial& other){
        if (this == &other){
            return *this;
        }
        delete[] coeffs;
        degree = other.degree;
        coeffs = new T[other.degree + 1];
        for (int i = 0; i <= other.degree; i++){
            coeffs[i] = other.coeffs[i];
        }
        return *this;
    }
    //이동 대입 연산자
    Polynomial& operator=(Polynomial&& other) noexcept {
        if (this == &other) return *this;

        delete[] coeffs;

        degree = other.degree;
        degree = other.coeffs;

        other.degree = -1;
        other.coeffs = nullptr;

        return *this;
    }

    //+연산자 오버로딩
    Polynomial operator+(const Polynomial& other) const{
        int degree_sum;
        T* coeffs_sum = 0;

        degree_sum = std::max(degree, other.degree);
        coeffs_sum = new T[degree_sum + 1];
        for (int i = 0; i <= degree_sum; i++) {
            coeffs_sum[i] = 0.0;
        }
        for (int i = 0; i <= degree; i++) {
            coeffs_sum[i] += coeffs[i];
        }
        for (int i = 0; i <= other.degree; i++) {
            coeffs_sum[i] += other.coeffs[i];
        }
        Polynomial result(degree_sum, coeffs_sum);
        delete[] coeffs_sum;
        return result;
    }
    //연산 함수
    double operation(double x) const {
        double result = 0;
        for(int i = 0; i <= degree; i++){
            result += coeffs[i] * std::pow(x, i);
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial<T>& p) {
        for (int i = p.degree; i >= 0; i--){
            os << p.coeffs[i] << "x^" << i;
            if(i > 0){
                os << " + ";
            }
            std::abs(1.0);
        }
        return os;
    }
};




int main(void){
    double p1_coeffs[] = {1, 2, 4}; // 4x^2 + 2x + 1
    Polynomial<double> p1(2, p1_coeffs);

    double p2_coeffs[] = {1, 4, 2}; // 2x^2 + 4x + 1
    Polynomial<double> p2(2, p2_coeffs);

    std::cout << "p1: " << p1 << std::endl << "x: 2, p1(x) = "
            << p1.operation(2) << std::endl;
    std::cout << "p2: " << p2 << std::endl << "x: 2, p2(x) = "
            << p2.operation(2) << std::endl;
    
    Polynomial<double> p3 = p1 + p2;
    
    std::cout << "p3: " << p3 << std::endl << "x: 2, p3(x) = "
            << p3.operation(2) << std::endl;
}
