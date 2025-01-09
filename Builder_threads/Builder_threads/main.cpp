#include <iostream>
#include <string>
#include <mutex>
#include <string_view>
#include <syncstream>
#include <thread>
using namespace std;

/*  Przyk³ad konfiguracji komputeró - wzorzec Budowniczy
*   Problem ze wzorcem polega na tym, ¿e konfigurowane s¹ komputery z identycznymi parametrami.
*   Do poprawki na zajêciach.
*/

class Computer {
public:
    Computer() {};
    Computer(const string& cpu, const string& memory, const string& storage) :
        cpu_(cpu_), memory_(memory), storage_(storage) {
    };

    void setCPU(const std::string cpu) {
        cpu_ = cpu;
    }

    void setMemory(const std::string memory) {
        memory_ = memory;
    }

    void setStorage(const std::string storage) {
        storage_ = storage;
    }

    void display() {
        std::cout << "CPU     " << cpu_ << endl;
        std::cout << "Memory  " << memory_ << endl;
        std::cout << "Storage " << storage_ << endl;
    }

private:
    std::string cpu_;
    std::string memory_;
    std::string storage_;
};

// Builder interface
class ComputerBuilder {
public:
    virtual void buildCPU(const std::string cpu) = 0;
    virtual void buildMemory(const std::string memory) = 0;
    virtual void buildStorage(const std::string storage) = 0;
    virtual Computer getResult() = 0;
};

// Concrete Builder
class DesktopComputerBuilder : public ComputerBuilder {
public:
    DesktopComputerBuilder() {
        computer_ = Computer();
    }

    void buildCPU(const std::string cpu) override {
        computer_.setCPU(cpu);
    }

    void buildMemory(const std::string memory) override {
        computer_.setMemory(memory);
    }

    void buildStorage(const std::string storage) override {
        computer_.setStorage(storage);
    }

    Computer getResult() override {
        return computer_;
    }

private:
    Computer computer_;
};

// Concrete Builder
class NotebookComputerBuilder : public ComputerBuilder {
public:
    NotebookComputerBuilder() {
        computer_ = Computer("i9-4600 Mobile", "32 GB", "1 TB");
    }

    void buildCPU(const std::string cpu) override {
        computer_.setCPU(cpu);
    }

    void buildMemory(const std::string memory) override {
        computer_.setMemory(memory);
    }

    void buildStorage(const std::string storage) override {
        computer_.setStorage(storage);
    }

    Computer getResult() override {
        return computer_;
    }

private:
    Computer computer_;
};

// Director
class ComputerAssembler {
public:
    Computer assembleComputer(ComputerBuilder& builder) {
        printf("\n %s \n", typeid(builder).name());
        if (typeid(builder) == typeid(DesktopComputerBuilder)) {
            printf("\n to jest typ %s \n", typeid(builder).name());
            builder.buildCPU("Intel i7");
            builder.buildMemory("16GB");
            builder.buildStorage("512GB SSD");
        }
        else if (typeid(builder) == typeid(NotebookComputerBuilder)) {
            printf("\n to jest typ %s \n", typeid(builder).name());
            builder.buildCPU("mobile Intel i5");
            builder.buildMemory("16GB");
            builder.buildStorage("512GB SSD");
        }
        return builder.getResult();
    }
};

class AppContext {
public:
    DesktopComputerBuilder desktopBuilder;
    NotebookComputerBuilder notebookBuilder;
    ComputerAssembler assembler;


   
};

/**
 * The Contener class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Contener
{

    /**
     * The Contener's constructor/destructor should always be private to
     * prevent direct construction/desctruction calls with the `new`/`delete`
     * operator.
     */
private:
    static Contener* pinstance_;
    static std::mutex mutex_;

protected:
    Contener(int cpu, int memory, int storage) 
        : quantity_of_cpus(cpu), quantity_of_memory(memory),quantity_of_storage(storage)
    {
    }
    ~Contener() {}

    int quantity_of_cpus;
    int quantity_of_memory;
    int quantity_of_storage;




public:



    /**
     * Conteners should not be cloneable.
     */
    Contener(Contener& other) = delete;
    /**
     * Conteners should not be assignable.
     */
    void operator=(const Contener&) = delete;
    /**
     * This is the static method that controls the access to the Contener
     * instance. On the first run, it creates a Contener object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    

    static Contener* GetInstance(int cpu, int memory, int storage);
    /**
     * Finally, any Contener should define some business logic, which can be
     * executed on its instance.
     */

   

    bool return_cpu()  {
        if (quantity_of_cpus > 0)
        {
            this->quantity_of_cpus -= 1;
            return true;
        }
        else
        {
            return false;
        }
       
    }
    
    bool return_memory()  {
        if (quantity_of_memory > 0)
        {
            this->quantity_of_memory -= 1;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool return_storage()  {
        if (quantity_of_storage > 0)
        {
            this->quantity_of_storage -= 1;
            return true;
        }
        else
        {
            return false;
        }
    }
    friend void Adding_aditional_stock();
};

/**
 * Static methods should be defined outside the class.
 */

Contener* Contener::pinstance_{ nullptr };
std::mutex Contener::mutex_;

/**
 * The first time we call GetInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value. RU:
 */
Contener* Contener::GetInstance(int cpu, int memory, int storage)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Contener(cpu, memory, storage);
    }
    return pinstance_;
}

void Adding_aditional_stock()
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Contener* magzyn = Contener::GetInstance(10, 10, 10);
        std::mutex mutex_;

        std::lock_guard<std::mutex> lock(mutex_);

        if (magzyn->quantity_of_cpus < 5)
        {
            magzyn->quantity_of_cpus = 5;
        }
        if (magzyn->quantity_of_memory < 5)
        {
            magzyn->quantity_of_memory = 5;
        }
        if (magzyn->quantity_of_storage < 5)
        {
            magzyn->quantity_of_storage = 5;
        }

        std::cout << magzyn->quantity_of_cpus << magzyn->quantity_of_memory << magzyn->quantity_of_storage << endl;
    }

}


void app_run_desktop() {
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        AppContext appContext;
        Contener* magzyn = Contener::GetInstance(10, 10, 10);
        if (magzyn->return_cpu())
        {
            if (magzyn->return_memory())
            {
                if (magzyn->return_storage())
                {
                    Computer desktop = appContext.assembler.assembleComputer(appContext.desktopBuilder);
                    std::cout << "Desktop Computer Configuration" << endl << endl;
                    desktop.display();
                }
            }
        }
        else
        {
            std::cout << "Computer configuration failed due to lack of resorces" << endl;
        }

       
    }

    
    
};

void app_run_netebook() {


    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        AppContext appContext;
        Contener* magzyn = Contener::GetInstance(10, 10, 10);
        if (magzyn->return_cpu())
        {
            if (magzyn->return_memory())
            {
                if (magzyn->return_storage())
                {
                    Computer notebook = appContext.assembler.assembleComputer(appContext.notebookBuilder);
                    std::cout << "Notebook Computer Configuration" << endl;
                    notebook.display();
                }
            }
        }
        else
        {
            std::cout << "Computer configuration failed due to lack of resorces" << endl;
        }


    }   

    
};




int main() {
    
    Contener* magazyn = Contener::GetInstance(10, 10, 10);

    std::thread t1(Adding_aditional_stock);

    std::thread t2(app_run_desktop);

    std::thread t3(app_run_netebook);

    



    t1.join();
    t2.join();
    t3.join();

    return 0;
}