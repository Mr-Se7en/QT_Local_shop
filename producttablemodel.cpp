#include "producttablemodel.h"

ProductTableModel::ProductTableModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

QVariant ProductTableModel::headerData(int section, Orientation orientation, int role) const
{
    {
        if (role == DisplayRole && orientation == Horizontal)
        {
            switch (section)
            {
            case 0:
                return "Product Name";
            case 1:
                return "ID";
            case 2:
                return "Price";
            case 3:
                return "Quantity";
            case 4:
                return "Type";
            case 5:
                return "Expiration Date";
            }
        }

        return QVariant();
    }
}

QModelIndex ProductTableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || row < 0 || row >= productList.size() || column < 0 || column >= 6)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex ProductTableModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int ProductTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return productList.size();
}

int ProductTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return 6;
}

QVariant ProductTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const PRODUCT &product = productList.at(index.row());

    switch (role)
    {
    case DisplayRole:
        switch (index.column())
        {
        case 0:
            return product.getproductName();
        case 1:
            return product.getId();
        case 2:
            return product.getPrice();
        case 3:
            return product.getQuantity();
        case 4:
            return product.getType();
        case 5:
            return product.getExpirationDate();
        }
        break;
    }

    return QVariant();
}

void ProductTableModel::setProductList(const QVector<PRODUCT> &products)
{
    beginResetModel();
    productList = products;
    endResetModel();
}

bool ProductTableModel::updateProduct(int row, const PRODUCT &product)
{
    if (row < 0 || row >= productList.size())
        return false;

    // Update the data at the specified row
    productList[row] = product;

    // Emit dataChanged signal to notify views about the specific change
    QModelIndex topLeft = index(row, 0);
    QModelIndex bottomRight = index(row, columnCount() - 1);
    emit dataChanged(topLeft, bottomRight);

    return true;
}

void ProductTableModel::addProduct(const PRODUCT &product)
{
    int newRow = rowCount(); // Get the row index for the new product
    beginInsertRows(QModelIndex(), newRow, newRow);

    // Add the new product to the vector
    productList.append(product);

    endInsertRows();
}

bool ProductTableModel::saveToFile(const QString &fileName)
{
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        // Write header
        out << "Product Name, ID, Price, Quantity, Type, Expiration Date\n";

        for (const PRODUCT &product : productList)
        {
            out << product.getproductName() << ","
                << product.getId() << ","
                << product.getPrice() << ","
                << product.getQuantity() << ","
                << product.getType() << ","
                << product.getExpirationDate() << "\n";
        }

        file.close();
        return true;
    }
    else
    {
        // Handle error opening the file
        qDebug() << "Error opening file for writing:" << file.errorString();
        return false;
    }
}

void ProductTableModel::loadFromFile(const QString &fileName)
{
    beginResetModel();

    QFile file(fileName);

    if (file.open( QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);

        // the first line is a header
        QString headerLine = in.readLine(); // Read the header line (if any)

        productList.clear();

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split(',');

            // Create a new PRODUCT object using the fields
            PRODUCT product(fields[1],
                            fields[0],
                            fields[2].toDouble(),
                            fields[3].toInt(),
                            fields[4],
                            fields[5]);

            productList.append(product);
        }

        file.close();

        endResetModel();
    }
    else
    {
        // Handle error opening the file
        qDebug() << "Error opening file for reading:" << file.errorString();
    }

}

bool ProductTableModel::removeProduct(int row)
{
    if (row < 0 || row >= productList.size())
        return false;

    beginRemoveRows(QModelIndex(), row, row);

    // Remove the product from the vector
    productList.removeAt(row);

    endRemoveRows();

    return true;
}

PRODUCT ProductTableModel::getProduct(int row) const
{
    if (row >= 0 && row < productList.size())
    {
        return productList.at(row);
    }
    else
    {
        // return empty PRODUCT
        return PRODUCT();
    }
}

int ProductTableModel::findProductIndex(const PRODUCT& product) const
{
    for (int i = 0; i < productList.size(); ++i)
    {
        if (productList.at(i) == product)
        {
            return i;
        }
    }

    return -1; // Return -1 if the product is not found
}
