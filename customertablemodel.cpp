// customertablemodel.cpp
#include "customertablemodel.h"

CustomerTableModel::CustomerTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant CustomerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "ID";
        case 1:
            return "Name";
        case 2:
            return "Credit Amount";
        case 3:
            return "Debit Amount";
        case 4:
            return "Contact Number";
        case 5:
            return "Address";
        default:
            break;
        }
    }
    return QVariant();
}

int CustomerTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return customerList.size();
}

int CustomerTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 6;
}

QVariant CustomerTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const CUSTOMER &customer = customerList.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0:
            return customer.getId();
        case 1:
            return customer.getName();
        case 2:
            return customer.getCreditAmount();
        case 3:
            return customer.getDebitAmount();
        case 4:
            return customer.getContactNumber();
        case 5:
            return customer.getAddress();
        default:
            break;
        }
    }

    return QVariant();
}

Qt::ItemFlags CustomerTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractTableModel::flags(index);
}

bool CustomerTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    CUSTOMER &customer = customerList[index.row()];

    switch (index.column())
    {
    case 2:
        customer.setCreditAmount(value.toDouble());
        break;
    case 3:
        customer.setDebitAmount(value.toDouble());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

void CustomerTableModel::addCustomer(const CUSTOMER &customer)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    customerList.append(customer);
    endInsertRows();
}

bool CustomerTableModel::updateCustomer(int row, const CUSTOMER &customer)
{
    if (row < 0 || row >= rowCount())
        return false;

    customerList[row] = customer;

    QModelIndex topLeft = index(row, 0);
    QModelIndex bottomRight = index(row, columnCount() - 1);
    emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole, Qt::EditRole});

    return true;
}

bool CustomerTableModel::removeCustomer(int row)
{
    if (row < 0 || row >= rowCount())
        return false;

    beginRemoveRows(QModelIndex(), row, row);
    customerList.removeAt(row);
    endRemoveRows();

    return true;
}

int CustomerTableModel::findCustomerIndex(const QString &customerId) const
{
    for (int i = 0; i < customerList.size(); ++i)
    {
        if (customerList.at(i).getId() == customerId)
        {
            return i;
        }
    }

    return -1; // Return -1 if the customer is not found
}

bool CustomerTableModel::checkAndHandleDuplication(const CUSTOMER &customer, double totalAmountPurchased, double amountPaid)
{
    int existingIndex = customerList.indexOf(customer);
    if (existingIndex != -1)
    {
        CUSTOMER &existingCustomer = customerList[existingIndex];

        double debt = totalAmountPurchased - amountPaid;

        if (debt <= 0) // Customer paid more than owed or equal
        {
            existingCustomer.setCreditAmount(existingCustomer.getCreditAmount() + debt * (-1));
        }
        else // Customer owes money
        {
            existingCustomer.setDebitAmount(existingCustomer.getDebitAmount() + debt);
        }

        // Ensure debt and credit amounts are consistent
        adjustDebtAndCredit(existingCustomer);

        // Update the existing customer in the model
        updateCustomer(existingIndex, existingCustomer);

        return true; // Customer is a duplicate
    }

    return false; // Customer is not a duplicate
}

void CustomerTableModel::adjustDebtAndCredit(CUSTOMER &customer)
{
    if (customer.getDebitAmount() > customer.getCreditAmount())
    {
        customer.setDebitAmount(customer.getDebitAmount() - customer.getCreditAmount());
        customer.setCreditAmount(0);
    }
    else if (customer.getDebitAmount() < customer.getCreditAmount())
    {
        customer.setCreditAmount(customer.getCreditAmount() - customer.getDebitAmount());
        customer.setDebitAmount(0);
    }
    else
    {
        customer.setCreditAmount(0);
        customer.setDebitAmount(0);
    }
}


bool CustomerTableModel::addCustomer(const CUSTOMER &newCustomer, double totalAmountPurchased, double amountPaid)
{
    // Check for duplication
    int existingIndex = customerList.indexOf(newCustomer);
    if (existingIndex != -1)
    {
        checkAndHandleDuplication(newCustomer, totalAmountPurchased, amountPaid);
        return false;
    }
    CUSTOMER neoCustomer=newCustomer;
    neoCustomer.setCreditAmount(neoCustomer.getCreditAmount()+amountPaid);
    neoCustomer.setDebitAmount(neoCustomer.getDebitAmount()+totalAmountPurchased);
    adjustDebtAndCredit(neoCustomer);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    customerList.append(neoCustomer);
    endInsertRows();


    return true;
}

void CustomerTableModel::saveToFile(const QString &fileName)
{
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        // Write header if
        out << "ID, Name, Credit Amount, Debit Amount, Contact Number, Address\n";

        for (const CUSTOMER &customer : customerList)
        {
            out << customer.getId() << ","
                << customer.getName() << ","
                << customer.getCreditAmount() << ","
                << customer.getDebitAmount() << ","
                << customer.getContactNumber() << ","
                << customer.getAddress() << "\n";
        }

        file.close();
    }
    else
    {
        qDebug() << "Error opening file for writing:" << file.errorString();
    }
}

void CustomerTableModel::loadFromFile(const QString &fileName)
{
    beginResetModel();

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        //the first line is a header
        QString headerLine = in.readLine(); // Read the header line (if any)

        customerList.clear();

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split(',');

            CUSTOMER customer(fields[0],
                              fields[1],
                              fields[2].toDouble(),
                              fields[3].toDouble(),
                              fields[4],
                              fields[5]);

            customerList.append(customer);
        }

        file.close();

        endResetModel();
    }
    else
    {
        qDebug() << "Error opening file for reading:" << file.errorString();
    }
}
