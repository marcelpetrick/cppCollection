//! Sum all values in the container.
auto const progressMaximum = std::accumulate(input.begin(), input.end(), 0);

// ---------------------------------------------------------------------------

//! Rename the key of some entry in a std::map. (C++17)
std::map<std::string, int> entries;
auto node = entries.extract(oldName);
node.key() = newName; // explodes here, because std::string does not like to be touched
entries.insert(std::move(node));

// ---------------------------------------------------------------------------

//! Return several return-values as tuple and split this automatically
// func:
std::tuple<float, float, float>
Device::getProperties() const
{
    return std::make_tuple(1.0f, 2.0f, 3.0f);
}
// the call:
auto [time, length, freq] = getProperties(); // (✿◠‿◠)

// ---------------------------------------------------------------------------

//! Get the user-name (based on the user-dir-pathname)
QString
Settings::getUserName() const
{
    auto const homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    auto const userName = homePath.first().split(QRegExp("[/\\\\]")).last(); // necessary, because QDir::separator() does not fit everytime on Win
    return userName;
}

// ---------------------------------------------------------------------------

//! Handle checkstate for all direct children of an item in a QTreeWidget

// connect
connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &TreeDialog::slotHandleCheckStates));

// handler
void
TreeDialog::slotHandleCheckStates(QTreeWidgetItem* item, int column)
{
    auto const currentCheckState = item->checkState(0);
    for(int i = 0; i < item->childCount(); ++i)
    {
       item->child(i)->setCheckState(0, currentCheckState);
    }
}

// ---------------------------------------------------------------------------

//! Colorize the text of some line-edit in case the entered data is not a valid file.
//! Combines Qt5-connect with a lambda.

// the connect and lambda
    connect(ui->lineEdit, &QLineEdit::textChanged,
                        [=] () {
        auto const isFile(fileExists(ui->lineEdit->text()));
        ui->lineEdit->setStyleSheet(isFile ? "color: black" : "color: red");
    });

// the file-existance check
bool
ReportGeneratorDialog::fileExists(QString path) const
{
    QFileInfo 🗄️(path);
    auto const returnValue = 🗄️.isFile() && 🗄️.exists();
    return returnValue;
}

// ---------------------------------------------------------------------------
