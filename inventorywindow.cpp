#include "inventorywindow.h"
#include "inventoryrestockdlg.h"
#include "invevntoryaddproductdialog.h"
#include "ui_inventorywindow.h"

#include"producttablemodel.h"

inventoryWindow::inventoryWindow(DataManager *manager,ProductTableModel *model,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inventoryWindow),modelPTR(model),manager(manager)
{
    ui->setupUi(this);
    ui->tableView->setModel(modelPTR);
    ui->tableView->update();
    connect(ui->tableView, &QTableView::clicked, this, &inventoryWindow::onItemClicked);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &inventoryWindow::onSelectionChanged);
}

inventoryWindow::~inventoryWindow()
{
    delete ui;
}

void inventoryWindow::closeEvent(QCloseEvent *event)
{
        QMessageBox msgBox;
        msgBox.setText("Do you want to save?");
        msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel|QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes:
            modelPTR->saveToFile(modelPTR->getSavePath());
            parent_pointer->show();
            QMainWindow::closeEvent(event);
            break;
        case QMessageBox::No:
            parent_pointer->show();
            QMainWindow::closeEvent(event);
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        }
}

void inventoryWindow::on_actionAdd_inventory_triggered()
{
    InvevntoryAddProductDialog addProductDialog(this);

    if (addProductDialog.exec() == QDialog::Accepted)
    {
        // User clicked OK
        PRODUCT newProduct = addProductDialog.getProduct();
        modelPTR->addProduct(newProduct);
        manager->addExpence(newProduct.getPrice()*newProduct.getQuantity());
    }
}


void inventoryWindow::on_actionRemove_inventory_triggered()
{
    modelPTR->removeProduct(currentrow);
    currentrow=-1;
}


void inventoryWindow::onItemClicked(const QModelIndex &index)
{
    // Disconnect the selectionChanged signal temporarily
    disconnect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &inventoryWindow::onSelectionChanged);

    int selectedRow = index.row();
    currentrow = selectedRow;
    qDebug() << "Selected Row: " << selectedRow;

    // Get the selection model
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    // Clear the current selection
    selectionModel->clear();

    // Select the entire row
    for (int x = 0; x < 6; x++) {
        selectionModel->select(index.siblingAtColumn(x), QItemSelectionModel::Select);
    }
    QVariant data = modelPTR->data(index, Qt::DisplayRole);
    qDebug() << "Data in clicked item: " << data;

    // Reconnect the selectionChanged signal
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &inventoryWindow::onSelectionChanged);
}



void inventoryWindow::on_actionRestock_inventory_triggered()
{
    if (currentrow>=0)
    {
        // Retrieve the product from the model
        PRODUCT selectedProduct = modelPTR->getProduct(currentrow);


        //the restock dialog
        InventoryRestockDlg restockDialog(this);
        if (restockDialog.exec() == QDialog::Accepted)
        {
            int restockQuantity = restockDialog.getRestockQuantity();
            manager->addExpence(selectedProduct.getPrice()*restockQuantity);
            // Update the quantity
            selectedProduct.setQuantity(selectedProduct.getQuantity() + restockQuantity);

            // Update the model
            modelPTR->updateProduct(currentrow, selectedProduct);
        }
    }
    currentrow=-1;
}



void inventoryWindow::on_actionEditInventory_triggered()
{   PRODUCT selectedProduct = modelPTR->getProduct(currentrow);

    InvevntoryAddProductDialog addProductDialog(selectedProduct,this);

    if (addProductDialog.exec() == QDialog::Accepted)
    {
        // User clicked OK
        PRODUCT newProduct = addProductDialog.getProduct();
        modelPTR->updateProduct(currentrow,newProduct);
    }
}

void inventoryWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // Check if any items are selected
    if (selected.indexes().isEmpty()) {
        // No item selected, reset currentrow
        currentrow = -1;
    } else {
        // Get the selected row
        int selectedRow = selected.indexes().first().row();
        currentrow = selectedRow;
        qDebug() << "Selected Row: " << selectedRow;
    }
}

void inventoryWindow::on_actionSave_triggered()
{
    bool succ=modelPTR->saveToFile(modelPTR->getSavePath());
    if(succ)
    {
        QMessageBox msgBox;
        msgBox.setText("save succesfull");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("save failed");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

