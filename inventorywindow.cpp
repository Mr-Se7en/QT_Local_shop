#include "inventorywindow.h"
#include "inventoryrestockdlg.h"
#include "invevntoryaddproductdialog.h"
#include "ui_inventorywindow.h"

#include"producttablemodel.h"

inventoryWindow::inventoryWindow(ProductTableModel *model,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inventoryWindow),modelPTR(model)
{
    ui->setupUi(this);
    ui->tableView->setModel(modelPTR);
    ui->tableView->update();
    ui->centralwidget->adjustSize();
    connect(ui->tableView, &QTableView::clicked, this, &inventoryWindow::onItemClicked);
}

inventoryWindow::~inventoryWindow()
{
    delete ui;
}

void inventoryWindow::closeEvent(QCloseEvent *event)
{
    parent_pointer->show();
    QMainWindow::closeEvent(event);
}

void inventoryWindow::on_actionAdd_inventory_triggered()
{
    InvevntoryAddProductDialog addProductDialog(this);

    // Show the dialog as a modal dialog
    if (addProductDialog.exec() == QDialog::Accepted)
    {
        // User clicked "OK," retrieve the product and add it to the table
        PRODUCT newProduct = addProductDialog.getProduct();
        modelPTR->addProduct(newProduct);
    }
    ui->centralwidget->adjustSize();
}


void inventoryWindow::on_actionRemove_inventory_triggered()
{
    modelPTR->removeProduct(currentrow);
    currentrow=-1;
}


void inventoryWindow::onItemClicked(const QModelIndex &index)
{
    int selectedRow = index.row();
    currentrow=selectedRow;
    qDebug() << "Selected Row: " << selectedRow;

    // Get the selection model from the table view
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    // Clear the current selection
    selectionModel->clear();

    // Select the entire row of the clicked item
    for(int x=0;x<6;x++){
        selectionModel->select(index.siblingAtColumn(x), QItemSelectionModel::Select);
    }
    // Add more columns if needed

    // If you want to access the data in the clicked row, you can use the model
    QVariant data = modelPTR->data(index, Qt::DisplayRole);
    qDebug() << "Data in clicked item: " << data;
}


void inventoryWindow::on_actionRestock_inventory_triggered()
{
    if (currentrow>=0)
    {
        // Retrieve the product from the model
        PRODUCT selectedProduct = modelPTR->getProduct(currentrow);

        // Create and open the restock dialog
        InventoryRestockDlg restockDialog(this);
        if (restockDialog.exec() == QDialog::Accepted)
        {
            // Get the restock quantity from the dialog
            int restockQuantity = restockDialog.getRestockQuantity();

            // Update the quantity of the selected product
            selectedProduct.setQuantity(selectedProduct.getQuantity() + restockQuantity);

            // Update the model or data structure
            modelPTR->updateProduct(currentrow, selectedProduct);
        }
    }
    currentrow=-1;
}



void inventoryWindow::on_actionEditInventory_triggered()
{   PRODUCT selectedProduct = modelPTR->getProduct(currentrow);

    InvevntoryAddProductDialog addProductDialog(selectedProduct,this);

    // Show the dialog as a modal dialog
    if (addProductDialog.exec() == QDialog::Accepted)
    {
        // User clicked "OK," retrieve the product and add it to the table
        PRODUCT newProduct = addProductDialog.getProduct();
        modelPTR->updateProduct(currentrow,newProduct);
    }
}

