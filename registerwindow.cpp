#include "registerwindow.h"
#include "inventoryrestockdlg.h"
#include "ui_registerwindow.h"

registerWindow::registerWindow(ProductTableModel *inventory_model,RegisterProductModel *register_model,QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::registerWindow),
    inventory_model(inventory_model),
    registerPTR(register_model)
{
    ui->setupUi(this);
    ui->tableView->setModel(registerPTR);
    addProductDialog = new RegisterAddDlg (inventory_model, this);
    dealsAggregator=new DealsAggregator(inventory_model,this);
    connect(this,&registerWindow::removeitem,dealsAggregator,&DealsAggregator::removeitem);
    connect(ui->tableView, &QTableView::clicked, this, &registerWindow::onItemClicked);
    connect(this,&registerWindow::confirmOrder,registerPTR,&RegisterProductModel::confirmOrder);
    connect(addProductDialog, &RegisterAddDlg::sendSelected, dealsAggregator, &DealsAggregator::addDeal);
    connect(dealsAggregator, &DealsAggregator::ItemToRegister, registerPTR, &RegisterProductModel::additem);
    connect(dealsAggregator,&DealsAggregator::UpdateProduct,registerPTR,&RegisterProductModel::UpdateProduct);
    connect(this,&registerWindow::EditItem,dealsAggregator,&DealsAggregator::EditItem);
    connect(this,&registerWindow::discard,dealsAggregator,&DealsAggregator::discard);
}

registerWindow::~registerWindow()
{
    delete ui;
//    delete parent_pointer;

}
void registerWindow::closeEvent(QCloseEvent *event)
{
    parent_pointer->show();
    QMainWindow::closeEvent(event);
}
void registerWindow::onItemClicked(const QModelIndex &index)
{
    // Disconnect the selectionChanged signal temporarily
    disconnect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &registerWindow::onSelectionChanged);

    int selectedRow = index.row();
    currentrow = selectedRow;
    qDebug() << "Selected Row: " << selectedRow;

    // Get the selection model from the table view
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    // Clear the current selection
    selectionModel->clear();

    // Select the entire row of the clicked item
    for (int x = 0; x < 6; x++) {
        selectionModel->select(index.siblingAtColumn(x), QItemSelectionModel::Select);
    }
    // Add more columns if needed

    // If you want to access the data in the clicked row, you can use the model
    QVariant data = registerPTR->data(index, Qt::DisplayRole);
    qDebug() << "Data in clicked item: " << data;

    // Reconnect the selectionChanged signal
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &registerWindow::onSelectionChanged);
}


void registerWindow::on_actionADD_triggered()
{


    // Show the dialog as a modal dialog
    addProductDialog->exec();
}


void registerWindow::on_actionRemove_triggered()
{
    if(currentrow>=0)
    {   emit removeitem(currentrow);
        registerPTR->removeProduct(currentrow);
        currentrow=-1;
    }
}

void registerWindow::on_actionConfirm_order_triggered()
{
    emit confirmOrder();
}


void registerWindow::on_actionEdit_triggered()
{
    if (currentrow>=0)
    {
        // Retrieve the product from the model
        PRODUCT selectedProduct = registerPTR->getProduct(currentrow);

        // Create and open the restock dialog
        InventoryRestockDlg restockDialog(this);
        if (restockDialog.exec() == QDialog::Accepted)
        {
            // Get the restock quantity from the dialog
            int resetQuantity = restockDialog.getRestockQuantity();
            emit EditItem(currentrow,selectedProduct,resetQuantity);

            // Update the model or data structure
//            registerPTR->updateProduct(currentrow, selectedProduct);
        }
    }
    currentrow=-1;
}

void registerWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
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

void registerWindow::on_actionDiscard_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to discard?");
    //    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    QVector<PRODUCT>empty;
    switch (ret) {
    case QMessageBox::Yes:
        registerPTR->setProductList(empty);
        emit discard();
        break;
    case QMessageBox::Cancel:
        break;
    }
}

