#include <gtkmm.h>
#include <gtkmm/builder.h>
#include <iostream>

class MyWindow : public Gtk::Window {
public:

    MyWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    : Gtk::Window(cobject), times(0), refGlade_(refGlade) {
        // 获取按钮
        Gtk::Button* btn = nullptr;
        refGlade_->get_widget("btn", btn);

        if (btn) {
            // 连接点击信号
            btn->signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::onBtnClicked));
        }

        Gtk::Label* lbl = nullptr;
        refGlade_->get_widget("lbl", lbl);
    }

private:

    int times;
    Glib::RefPtr<Gtk::Builder> refGlade_;
    
    void onBtnClicked() {
        // 在此处添加按钮点击时的处理逻辑
//        std::cout << "按钮被点击了" << std::endl;
        times++;
        
        std::string countStr = "点击了 " + std::to_string(times) + " 次";
        Gtk::Label* lbl = nullptr;
        refGlade_->get_widget("lbl", lbl);
        if (lbl) {
            lbl->set_text(countStr);
        }
    }
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.example.myapp");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    try {
        builder->add_from_file("ui.glade");
    }    catch (const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }    catch (const Gtk::BuilderError& ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    MyWindow* mainWindow = nullptr;
    builder->get_widget_derived("main_window_id", mainWindow);

    app->run(*mainWindow);

    return 0;
}
