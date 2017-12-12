/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#ifndef CRYINCLUDE_EDITOR_GENERICSELECTITEMDIALOG_H
#define CRYINCLUDE_EDITOR_GENERICSELECTITEMDIALOG_H
#pragma once

#include <QDialog>
#include <QScopedPointer>

// CGenericSelectItem dialog

namespace Ui {
    class CGenericSelectItemDialog;
}

class CGenericSelectItemDialog
    : public QDialog
{
    Q_OBJECT

public:
    typedef enum
    {
        eMODE_LIST, eMODE_TREE
    } TDialogMode;
    typedef IVariable::IGetCustomItems::SItem SItem;

    CGenericSelectItemDialog(QWidget* pParent = nullptr);   // standard constructor
    virtual ~CGenericSelectItemDialog();

    void ShowDescription(bool bShow)
    {
        m_bShowDesc = bShow;
    }

    virtual QString GetSelectedItem();

    virtual void PreSelectItem(const QString& name)
    {
        m_preselect = name;
    }

    void SetMode(TDialogMode inMode)
    {
        m_mode = inMode;
    }

    void AllowNew(bool bAllow)
    {
        m_bAllowNew = bAllow;
    }

    void SetTreeSeparator(const QString& sep)
    {
        m_treeSeparator = sep;
    }

    // Override items which are otherwise fetched by GetItems
    void SetItems(const QStringList& items)
    {
        m_bSet = true;
        m_items.resize(0);
        m_items.reserve(items.size());
        QStringList::const_iterator iter = items.begin();
        QStringList::const_iterator iterEnd = items.end();
        SItem item;
        while (iter != iterEnd)
        {
            item.name = item.desc = *iter;
            m_items.push_back(item);
            ++iter;
        }
    }

    // Override items which are otherwise fetched by GetItems
    void SetItems(const std::vector<QString>& items)
    {
        m_bSet = true;
        m_items.resize(0);
        m_items.reserve(items.size());
        std::vector<QString>::const_iterator iter = items.begin();
        std::vector<QString>::const_iterator iterEnd = items.end();
        SItem item;
        while (iter != iterEnd)
        {
            item.name = item.desc = *iter;
            m_items.push_back(item);
            ++iter;
        }
    }

    // Override items which are otherwise fetched by GetItems
    void SetItems(const std::vector<SItem>& items)
    {
        m_bSet = true;
        m_items = items;
    }

    void showEvent(QShowEvent* event) override;

    enum
    {
        New = QDialog::Accepted + 1
    };

protected:
    // Derived Dialogs should override this
    virtual void GetItems(std::vector<SItem>& outItems);

    // Called whenever an item gets selected
    virtual void ItemSelected();

    void OnTvnSelchangedTree();
    void OnTvnDoubleClick();
    void OnLbnSelchangeList();
    void OnLbnDoubleClick();
    void OnBnClickedNew();
    virtual void OnInitDialog();

    void ReloadItems();
    void ReloadTree();

    struct less_qstring_icmp
        : public std::binary_function<QString, QString, bool>
    {
        bool operator()(const QString& left, const QString& right) const
        {
            return QString::compare(left, right, Qt::CaseInsensitive) < 0;
        }
    };

    QString m_preselect;
    QString m_selectedItem;
    QString m_selectedDesc;
    QString m_treeSeparator;

    std::vector<SItem> m_items;
    TDialogMode m_mode;
    bool m_bSet;
    bool m_bAllowNew;
    bool m_bShowDesc;

    QScopedPointer<Ui::CGenericSelectItemDialog> ui;

private:
    bool m_initialized;
};

#endif // CRYINCLUDE_EDITOR_GENERICSELECTITEMDIALOG_H