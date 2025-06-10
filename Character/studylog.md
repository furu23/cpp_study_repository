# RPG 클래스 학습 로그

## 📖 개요
    객체지향의 특성과 가장 중요한 특징 중 하나인 상속성에 대한 공부를 진행했습니다. 동시에 STL 컨테이너와 메서드 체이닝 같은 것들 또한 활용해 보았습니다.
## 🔥 핵심 기능
- **`Character` 추상 클래스**: `Mage`와 `Warrior`의 발판이 되는 기반 클래스. 순수 가상 함수 attack()을 가지고 있어, 파생 클래스가 반드시 구현해야 할 인터페이스를 정의합니다.
- **`Mage`, `Warrior` 클래스**: `Character`를 상속받아 `attack` 메서드를 오버라이딩 합니다. 고유의 멤버 함수와 변수를 가지고 있습니다.
- `unique_ptr`, `vector` 등을 통한 RAII 설계 원칙을 지키도록 시도했습니다.
## 🔎 배운 것들
### 1. 상속
- 객체 지향 언어의 핵심 중의 핵심, 상속에 대한 학습을 진행했습니다.
- `public`, `private`, `protected`의 접근 제어자들에 대해 학습하고 그 차이를 확인했습니다.
```c++
// 멤버에 대한 권한에 더불어, 상속 시의 권한 설정 또한 학습했습니다.
class Warrior final : public Character{
        private:
        std::string weapon;
        public:
        ...
}
```
### 2. 상위 클래스
- 포인터를 통한 삭제 호출이 만드는 메모리 누수를 막기 위해 가상 호출자의 필요성과 사용법을 명확히 익혔습니다.
- 순수 가상 함수를 통한 인터페이스(여기서는 추상 클래스)의 구현에 대해 익혔습니다.
```c++
class Character{
    // 상속 관계 시 메모리 관리를 위한 필수적인 가상 소멸자에 대해 배웠습니다.
    ...
    virtual ~Character() = default;
    virtual void attack(void) const = 0;
    ...
};
```
### 3. 다양한 기능
- `namespace`, `using`, 범위 기반 `for` 루프 등 다양한 c++의 기능을 사용해보았습니다.
- `unique_ptr`, `vector`, `string` 등 STL 컨테이너들도 접해보았습니다. 더불어 RAII에 대한 지식을 얻고, 설계 원칙을 지키려고 노력해보았습니다.
```c++
// 스마트 포인터를 벡터 안에 저장하는 방식으로 RAII를 염두했다
int main(void){
    std::vector<CharacterPtr> characeters;
    characeters.push_back(std::make_unique<RPG::Warrior>("Thor", 150, 10, "Hammer"));
    characeters.push_back(std::make_unique<RPG::Mage>("Gandalf", 100, 12, "Ligntening"));
    ...
}
```
### 🚀 트러블 슈팅: 그냥 만들면 되는거 아니였나요?
> [!CAUTION]
> **⚠️오류: 팩토리? 그게 뭐야?**
>
> 템플릿 인자, 그냥 넣으면 안되나? 캐스팅, 어느 정보를 담아야 할지. unique_ptr를 처음 써보자, 에러에 저는 파묻혀버렸습니다. 게다가 이렇게 만들면 안된다는 피드백까지 받자 아찔해졌습니다.

> [!TIP]
> **✅해결: make_unique에 더불어서 더 나아가기!**
>
> 오류를 해결하기 위해, 레퍼런스 문서와 AI 질문을 애용했습니다. 그럼과 동시에 팩토리 패턴과, 이동 시맨틱스에 대한 지식도 추가로 얻을 수 있었습니다. 그를 통한 추가적인 발전을 얻은 셈이었습니다.

## ✨ 정리하며

특별한 것은 없는 상속을 배우는 간단한 설계임에도, 생각할 것이 아주 많다는 것을 깨닫게 해준 작업이었습니다. 또한, 다양한 기능들을 써보며 더 나아갈 발판이 되었다고 생각합니다.