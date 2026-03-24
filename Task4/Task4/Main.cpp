#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // 검색 로직을 위해 추가

class PotionRecipe
{
public:
    std::string potionName;
    std::vector<std::string> ingredients;

    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients)
    {
    }

    // 레시피 한 개를 예쁘게 출력하는 보조 함수
    void print() const
    {
        std::cout << "- 물약 이름: " << potionName << "\n  > 필요 재료: ";
        for (size_t i = 0; i < ingredients.size(); ++i)
        {
            std::cout << ingredients[i] << (i < ingredients.size() - 1 ? ", " : "");
        }
        std::cout << std::endl;
    }
};

class AlchemyWorkshop
{
private:
    std::vector<PotionRecipe> recipes;

public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    void displayAllRecipes() const
    {
        if (recipes.empty())
        {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }
        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (const auto& r : recipes) r.print();
        std::cout << "---------------------------\n";
    }

    // 1. 물약 이름으로 검색 (중복 없다고 가정)
    void searchByName(const std::string& name) const
    {
        for (const auto& r : recipes)
        {
            if (r.potionName == name)
            {
                std::cout << "[검색 결과]\n";
                r.print();
                return;
            }
        }
        std::cout << ">> '" << name << "' 레시피를 찾을 수 없습니다." << std::endl;
    }

    // 2. 재료로 검색 (해당 재료가 포함된 모든 레시피 출력)
    void searchByIngredient(const std::string& target) const
    {
        bool found = false;
        std::cout << "[ '" << target << "'(이)가 포함된 레시피 ]\n";
        for (const auto& r : recipes)
        {
            for (const auto& ing : r.ingredients)
            {
                if (ing == target)
                {
                    r.print();
                    found = true;
                    break;
                }
            }
        }
        if (!found) std::cout << ">> 해당 재료가 사용된 레시피가 없습니다." << std::endl;
    }
};

int main()
{
    AlchemyWorkshop myWorkshop;
    int choice;

    while (true)
    {
        std::cout << "\n?? 연금술 공방 관리 시스템\n1. 추가 | 2. 전체출력 | 3. 이름검색 | 4. 재료검색 | 5. 종료\n선택: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear(); std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            std::string name, ing;
            std::vector<std::string> ings;
            std::cout << "물약 이름: ";
            std::cin.ignore(); std::getline(std::cin, name);
            std::cout << "재료 입력 ('끝' 입력 시 중단): \n";
            while (true)
            {
                std::cout << "- "; std::getline(std::cin, ing);
                if (ing == "끝") break;
                ings.push_back(ing);
            }
            if (!ings.empty()) myWorkshop.addRecipe(name, ings);
        }
        else if (choice == 2) myWorkshop.displayAllRecipes();
        else if (choice == 3)
        {
            std::string name;
            std::cout << "찾을 물약 이름: ";
            std::cin.ignore(); std::getline(std::cin, name);
            myWorkshop.searchByName(name);
        }
        else if (choice == 4)
        {
            std::string ing;
            std::cout << "찾을 재료 이름: ";
            std::cin.ignore(); std::getline(std::cin, ing);
            myWorkshop.searchByIngredient(ing);
        }
        else if (choice == 5) break;
    }
    return 0;
}