#include <QDialog>
#include "ErrorHandler.h"

class PanelInterface : public QDialog {
public:
    virtual void showPanel() {
        this->show();
    }

    virtual void hidePanel() {
        this->hide();
    }
    virtual ~PanelInterface() = default;
    explicit PanelInterface(QWidget* parent = nullptr)
        : QDialog(parent) {}
};

